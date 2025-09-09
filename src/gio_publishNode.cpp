#include <ros/ros.h>
#include "my_first_project/gio_path.h"
#include <volksbot/vels.h>  // rostopic  info /Vel


std::ofstream giodat;

int main(int argc, char **argv) {
    ros::init(argc, argv, "gio_node");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<volksbot::vels>("/Vel", 10);// mit 

    CGioController controller;
    controller.setPose(0.0, 0.0, 0.0);

    ros::Rate loop(10);
    while (ros::ok()) {
        double u, w, vleft, vright;
        if (controller.getNextState(u, w, vleft, vright, 0)) {
            volksbot::vels vel_msg;
            vel_msg.left  = vleft;
            vel_msg.right = vright;
            vel_msg.id    = 0;
            vel_pub.publish(vel_msg);
        }
        ros::spinOnce();
        loop.sleep();
    }
    ROS_INFO("ich bin durch!");
}

