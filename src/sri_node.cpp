// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#include <ros/ros.h>
#include <sri_com.h>

int iter_trame = 0;
int length_trame = 255;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node_name");

    ros::NodeHandle n;

    int serial_port = open("/dev/serial/by-id/usb-Arduino_LLC_Arduino_Micro-if00", O_RDWR);

    uint8_t read_buf[256];

    ROS_INFO("TEST");
    ros::Rate r(100);
    while (n.ok())
    {
        memset(&read_buf, '\0', sizeof(read_buf));

        int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

        for (int i = 0; i < num_bytes; i++)
        {
            ROS_INFO("byte : %x",read_buf[i]);
            if (iter_trame == 0 && read_buf[i] == 0xfe)
            {
                iter_trame++;
                ROS_INFO("START");
            }
            else if (iter_trame == 1)
            {
                length_trame = (int)read_buf[i] + 6;
                iter_trame++;
                ROS_INFO("length : %d",length_trame);
            }
            else if (iter_trame == 2)
            {
                //check for packet loss with sequencing
                iter_trame++;
                ROS_INFO("sequence : %d",(int)read_buf[i]);
            }
            else if (iter_trame == 3)
            {
                //check the identity
                iter_trame++;
                ROS_INFO("identity : %d",(int)read_buf[i]);
            }
            else if (iter_trame == 4)
            {
                //type de message
                iter_trame++;
                ROS_INFO("Type : %d",(int)read_buf[i]);
            }
            else if (iter_trame>=5 && iter_trame< length_trame)
            {
                //payload
                iter_trame++;
                ROS_INFO("payload : %x",read_buf[i]);
            }
            else if (iter_trame == length_trame)
            {
                //checksum
                iter_trame = 0;
                ROS_INFO("checksum : %x",read_buf[i]);
            }
            
        }
        ros::spinOnce();
        r.sleep();
    }
}