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
#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/UInt16MultiArray.h>

int iter_trame = 0;
int length_trame = 255;
bool trame_complete = false;
uint8_t trame[261];

std::string emitter_basic_topic = "emitter_";
std::string emitter_topic;

extern ros::NodeHandle n;

std::vector<std::vector<ros::Publisher> > publisher;

int CheckForEmitter(int number)
{
    emitter_topic = emitter_basic_topic + std::to_string(number);
    for (int i = 0; i < publisher.size(); i++)
    {
        if (publisher[i][0].getTopic().find(emitter_topic) != std::string::npos)
        {
            return i;
        }
    }
    publisher.push_back(std::vector<ros::Publisher>());
    return publisher.size() - 1;
}

int CheckForMsgType(std::string msg_type, int number)
{
    for (int i = 0; i < publisher[number].size(); i++)
    {
        if (publisher[number][i].getTopic().find(msg_type) != std::string::npos)
        {
            return i;
        }
    }
    publisher[number].push_back(ros::Publisher());
    return publisher[number].size() - 1;
}

void PublishInt8(ros::NodeHandle n, std::string msg_type_name)
{
    int num1 = CheckForEmitter((int)trame[3]);
    int num2 = CheckForMsgType(msg_type_name, num1);
    if (publisher[num1][num2].getTopic() == "")
    {
        std::string topic = "/" + emitter_topic + "/" + msg_type_name;
        publisher[num1][num2] = n.advertise<std_msgs::Int8MultiArray>(topic.c_str(), 1000);
    }
    std_msgs::Int8MultiArray _msg_int8;
    for (int i = 0; i < trame[1]; i++)
    {
        _msg_int8.data.push_back(trame[5 + i]);
    }
    publisher[num1][num2].publish(_msg_int8);
}

void PublishUInt8(ros::NodeHandle n, std::string msg_type_name)
{
    int num1 = CheckForEmitter((int)trame[3]);
    int num2 = CheckForMsgType(msg_type_name, num1);
    if (publisher[num1][num2].getTopic() == "")
    {
        std::string topic = "/" + emitter_topic + "/" + msg_type_name;
        publisher[num1][num2] = n.advertise<std_msgs::UInt8MultiArray>(topic.c_str(), 1000);
    }
    std_msgs::UInt8MultiArray _msg_uint8;
    for (int i = 0; i < trame[1]; i++)
    {
        _msg_uint8.data.push_back(trame[5 + i]);
    }
    publisher[num1][num2].publish(_msg_uint8);
}

void PublishInt16(ros::NodeHandle n, std::string msg_type_name)
{
    int num1 = CheckForEmitter((int)trame[3]);
    int num2 = CheckForMsgType(msg_type_name, num1);
    if (publisher[num1][num2].getTopic() == "")
    {
        std::string topic = "/" + emitter_topic + "/" + msg_type_name;
        publisher[num1][num2] = n.advertise<std_msgs::Int16MultiArray>(topic.c_str(), 1000);
    }
    std_msgs::Int16MultiArray _msg_int16;
    for (int i = 0; i < trame[1]; i = i + 2)
    {
        _msg_int16.data.push_back(((int16_t)trame[6 + i] << 8) | trame[5 + i]);
    }
    publisher[num1][num2].publish(_msg_int16);
}

void PublishUInt16(ros::NodeHandle n, std::string msg_type_name)
{
    int num1 = CheckForEmitter((int)trame[3]);
    int num2 = CheckForMsgType(msg_type_name, num1);
    if (publisher[num1][num2].getTopic() == "")
    {
        std::string topic = "/" + emitter_topic + "/" + msg_type_name;
        publisher[num1][num2] = n.advertise<std_msgs::UInt16MultiArray>(topic.c_str(), 1000);
    }
    std_msgs::UInt16MultiArray _msg_uint16;
    for (int i = 0; i < trame[1]; i = i + 2)
    {
        _msg_uint16.data.push_back(((uint16_t)trame[6 + i] << 8) | trame[5 + i]);
    }
    publisher[num1][num2].publish(_msg_uint16);
}

void PublishTrame(ros::NodeHandle n)
{
    switch (trame[4])
    {
    case t_INT8:
        PublishInt8(n,"msg_int8");
        break;
    case t_V2INT8:
        PublishInt8(n,"msg_v2_int8");
        break;
    case t_V3INT8:
        PublishInt8(n,"msg_v3_int8");
        break;
    case t_uINT8:
        PublishUInt8(n,"msg_uint8");
        break;
    case t_V2uINT8:
        PublishUInt8(n,"msg_v2_uint8");
        break;
    case t_V3uINT8:
        PublishUInt8(n,"msg_v3_uint8");
        break;
    case t_INT16:
        PublishInt16(n,"msg_int16");
        break;
    case t_V2INT16:
        PublishInt16(n,"msg_v2_int16");
        break;
    case t_V3INT16:
        PublishInt16(n,"msg_v3_int16");
        break;
    case t_uINT16:
        PublishUInt16(n,"msg_uint16");
        break;
    case t_V2uINT16:
        PublishUInt16(n,"msg_v2_uint16");
        break;
    case t_V3uINT16:
        PublishUInt16(n,"msg_v3_uint16");
        break;

    default:
        break;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node_name");

    ros::NodeHandle n;

    int serial_port = open("/dev/serial/by-id/usb-Arduino_LLC_Arduino_Micro-if00", O_RDWR);

    uint8_t read_buf[256];

    ROS_INFO("TEST");
  /*   publisher.push_back(std::vector<ros::Publisher>());
    publisher[0].push_back(ros::Publisher());
    publisher[0][0] = n.advertise<std_msgs::Int8MultiArray>("/test/Test3", 100);
    ROS_INFO("%s", publisher[0][0].getTopic().c_str()); */
    ros::Rate r(1000);
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
                {
                    PublishTrame(n);
                    ROS_INFO("msg received without problem");
                }
                trame_complete = false;
            }
        }
        ros::spinOnce();
        r.sleep();
    }
}