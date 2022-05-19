#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def talker():
    # create a publisher, on topic `chatter`
    pub = rospy.Publisher('chatter', String, queue_size=10)

    # create a node
    rospy.init_node('talker', anonymous=True)

    # set the rate of publishing
    rate = rospy.Rate(1) # 1hz

    # main loop
    while not rospy.is_shutdown():
        # make content
        hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)

        # publish a message
        pub.publish(hello_str)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
