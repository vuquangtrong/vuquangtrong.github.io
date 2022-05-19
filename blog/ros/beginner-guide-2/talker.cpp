#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv)
{
    // init with a name
    ros::init(argc, argv, "talker");

    // create a node
    ros::NodeHandle n;

    // publish on a the `chatter` topic, queue = 1000
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>(
        "chatter",
        1000
    );

    // publishing rate 1 Hz
    ros::Rate loop_rate(1);

    // main loop
    int count = 0;
    while (ros::ok()) {
        // message
        std_msgs::String msg;

        // content
        std::stringstream ss;
        ss << "hello world " << count++;
        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str());

        // publish
        chatter_pub.publish(msg);

        // check status
        ros::spinOnce();

        // sleep
        loop_rate.sleep();
    }

    return 0;
}
