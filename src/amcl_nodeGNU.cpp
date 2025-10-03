//004   amcl_nodeGNU.amcl_pose
#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>// der Path der amcl_pose published
#include <fstream>
#include <tf/tf.h>

std::ofstream logfile;

void amclPosition(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) { //hier nochmal den Pfad angeben
    double x = msg->pose.pose.position.x;
    double y = msg->pose.pose.position.y;
    logfile << x << " " << y << " " << std::endl;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "amclPosition");
    ros::NodeHandle nh;

    logfile.open("/home/kian/catkin_ws/src/my_first_project/amcl_path.txt");
    if (!logfile.is_open()) {
        ROS_ERROR("Konnte odom_path.txt nicht oeffnen!");
        return 1;
    }else if (logfile.is_open()){
	    ROS_INFO("Konnte Connecten mein G");
    }

    ros::Subscriber sub = nh.subscribe("/amcl_pose", 1000, amclPosition);

    ros::spin();
    logfile.close();
    ROS_INFO("sollte funktioniert haben :Q");
    return 0;
}
