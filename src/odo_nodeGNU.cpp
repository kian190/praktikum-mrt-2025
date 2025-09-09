/*
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <fstream>
#include <tf/tf.h>   // für tf::getYaw

std::ofstream logfile;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    double x = msg->pose.pose.position.x;
    double y = msg->pose.pose.position.y;

    // Orientierung (Quaternion → Yaw)
    double qx = msg->pose.pose.orientation.x;
    double qy = msg->pose.pose.orientation.y;
    double qz = msg->pose.pose.orientation.z;
    double qw = msg->pose.pose.orientation.w;
    double yaw = tf::getYaw(tf::Quaternion(qx, qy, qz, qw));

    // Loggen als CSV: x y yaw
    logfile << x << " " << y << " " << yaw << std::endl;

    ROS_INFO("Odom Pose: x=%.2f y=%.2f yaw=%.2f rad", x, y, yaw);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "odom_logger");
    ros::NodeHandle nh;

    logfile.open("/home/kian/catkin_ws/src/my_first_project/odom_path.txt");
    if (!logfile.is_open()) {
        ROS_ERROR("Konnte odom_path.txt nicht zum Schreiben öffnen!");
        return 1;
    } else {
        ROS_INFO("Logger gestartet, schreibe nach odom_path.txt");
    }

    ros::Subscriber sub = nh.subscribe("/odom", 1000, odomCallback);

    ros::spin();

    logfile.close();
    ROS_INFO("Pfad wurde in odom_path.txt gespeichert.");
    return 0;
}
*/
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
        // Transformiere Pose von "odom" → "map"
        listener->transformPose("map", odom_pose, map_pose);

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

    // TransformListener puffert 10 Sekunden tf-Daten
    listener = new tf::TransformListener(ros::Duration(10));

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
