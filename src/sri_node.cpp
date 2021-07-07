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
bool trame_complete = false;
uint8_t trame[261];
HEADER header;
union msg_union
{
    msg_uint8 _uint8;
    msg_int8 _int8;
    msg_uint16 _uint16;
    msg_int16 _int16;

    msg_v2_uint8 _v2_uint8;
    msg_v2_int8 _v2_int8;
    msg_v2_uint16 _v2_uint16;
    msg_v2_int16 _v2_int16;

    msg_v3_uint8 _v3_uint8;
    msg_v3_int8 _v3_int8;
    msg_v3_uint16 _v3_uint16;
    msg_v3_int16 _v3_int16;
} msg_union;

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
            if (iter_trame == 0 && read_buf[i] == 0xfe)
            {
                trame[0] = read_buf[i];
                iter_trame++;
            }
            else if (iter_trame == length_trame - 1)
            {
                trame[iter_trame] = read_buf[i];
                iter_trame = 0;
                trame_complete = true;
            }
            else if (iter_trame > 0)
            {
                trame[iter_trame] = read_buf[i];
                if (iter_trame == 1)
                {
                    length_trame = (int)trame[1] + 6;
                }
                iter_trame++;
            }

            if (trame_complete)
            {
                uint8_t checksum = trame[0];
                for (int j = 1; j < length_trame - 1; j++)
                {
                    checksum ^= trame[j];
                }
                if (trame[length_trame - 1] == checksum)
                    ROS_INFO("msg received without problem");
                trame_complete = false;
            }
        }
        ros::spinOnce();
        r.sleep();
    }
}