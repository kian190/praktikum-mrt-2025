//007   odo_nodeGNU.notransform
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <fstream>

std::ofstream logfile;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    double x = msg->pose.pose.position.x;
    double y = msg->pose.pose.position.y;

    logfile << x << " " << y << std::endl;
    ROS_INFO("Odom roh: x=%.2f y=%.2f", x, y);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "odom_logger");
    ros::NodeHandle nh;

    logfile.open("/home/kian/catkin_ws/src/my_first_project/odom_path.txt");
    if (!logfile.is_open()) {
        ROS_ERROR("Konnte odom_path.txt nicht öffnen!");
        return 1;
    }
    ROS_INFO("Logger gestartet, schreibe nach odom_path.txt");

    ros::Subscriber sub = nh.subscribe("/odom", 1000, odomCallback);
    ros::spin();

    logfile.close();
    return 0;
}
