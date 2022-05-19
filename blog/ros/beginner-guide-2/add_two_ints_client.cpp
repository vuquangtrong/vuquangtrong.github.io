#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    // check args
    ros::init(argc, argv, "add_two_ints_client");
    if (argc != 3)
    {
        ROS_INFO("usage: add_two_ints_client X Y");
        return 1;
    }

    // create a node
    ros::NodeHandle n;

    // node will have a client
    ros::ServiceClient client = n.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");

    // create a service target
    beginner_tutorials::AddTwoInts srv;

    // add params
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    // call to service
    if (client.call(srv)) {
        ROS_INFO("Sum: %ld", (long int)srv.response.sum);
    } else {
    ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }

    return 0;
}
