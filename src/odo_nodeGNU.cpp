#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>
#include <fstream>

std::ofstream logfile;
tf::TransformListener* listener;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    geometry_msgs::PoseStamped odom_pose, map_pose;
    odom_pose.header = msg->header;
    odom_pose.pose   = msg->pose.pose;

    try {
        listener->transformPose("map", odom_pose, map_pose); // Transform "odom" → "map"

        double x = map_pose.pose.position.x;
        double y = map_pose.pose.position.y;

        logfile << x << " " << y << std::endl;
        ROS_INFO("Odom in map: x=%.2f y=%.2f", x, y);
    }
    catch (tf::TransformException &ex) {
        ROS_WARN("Transform error: %s", ex.what());
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "odom_to_map_logger");
    ros::NodeHandle nh;

    listener = new tf::TransformListener(ros::Duration(10));// to only save the Buffer 10 Sekonds

    logfile.open("/home/kian/catkin_ws/src/my_first_project/odom_path.txt");
    if (!logfile.is_open()) {
        ROS_ERROR("Konnte odom_in_map.txt nicht öffnen!");
        return 1;
    }
    ROS_INFO("Logger gestartet, schreibe nach odom_in_map.txt");

    ros::Subscriber sub = nh.subscribe("/odom", 1000, odomCallback);
    ros::spin();

    logfile.close();
    delete listener;
    return 0;
}
