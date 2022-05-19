#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
    // init with a name
    ros::init(argc, argv, "listener");

    // create a node
    ros::NodeHandle n;

    // subscribe on a the `chatter` topic, queue = 1000
    // execute chatterCallback on receive
    ros::Subscriber sub = n.subscribe(
        "chatter",
        1000,
        chatterCallback
    );

    // main loop
    ros::spin();

    return 0;
}
