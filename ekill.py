#!/usr/bin/env python3
# license removed for brevity
import rospy
from std_msgs.msg import Bool
import keyboard

def talker():
    pub = rospy.Publisher('spacebar_pressed', Bool, queue_size=10)
    rospy.init_node('spacebar_detector', anonymous=True)
    rate = rospy.Rate(10)  # 10Hz

    while not rospy.is_shutdown():
        spacebar_pressed = keyboard.is_pressed('space')
        rospy.loginfo(f"Spacebar Pressed: {spacebar_pressed}")
        pub.publish(spacebar_pressed)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
