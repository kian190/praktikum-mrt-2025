#include <ros/ros.h>
#include <signal.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/tf.h>
#include "my_first_project/gio_path.h"
#include "volksbot/vels.h"
#include <fstream>
#include <string>

struct State {
    ros::Publisher vel_pub;
    std::ofstream log;
    CGioController gio;

    double x=0, y=0, yaw=0;
    double t_prev=0, dt=0;

    double u=0, w=0, vL=0, vR=0;
    bool looped=false;

    double ox=0, oy=0;
    bool have_offset=false;

    double gx=0, gy=0, gyaw=0;

    const int gain = -60;
};

static void onSigint(int){ ros::shutdown(); }

int main(int argc, char** argv) {
    ros::init(argc, argv, "control_node", ros::init_options::NoSigintHandler);
    signal(SIGINT, onSigint);
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    State S;

    S.log.open("/home/kian/Downloads/Beispielpfade/giodat.txt");
    if(!S.log.is_open()){
        ROS_ERROR("Konnte giodat.txt nicht öffnen!");
        return 1;
    }

    const std::string filePath = "/home/kian/Downloads/Beispielpfade/acht.dat";
    if(!S.gio.getPathFromFile(filePath.c_str())){
        ROS_ERROR("Kann Pfaddatei nicht laden: %s", filePath.c_str());
        return -1;
    }

    S.vel_pub = nh.advertise<volksbot::vels>("/Vel", 10);

    bool use_amcl = false;
    pnh.param("use_amcl", use_amcl, false);
    for (int i=1;i<argc;i++) if (std::string(argv[i]) == "--use-amcl") use_amcl = true;

    S.t_prev = ros::Time::now().toSec();

    auto send = [&](){
        volksbot::vels m;
        m.left  = S.gain * S.vL;
        m.right = S.gain * S.vR;
        m.id    = 0;
        S.vel_pub.publish(m);

        //standart diff model
        S.gx   += S.u * std::cos(S.yaw) * S.dt;
        S.gy   += S.u * std::sin(S.yaw) * S.dt;
        S.gyaw += S.w * S.dt;
        S.log << S.gx << " " << S.gy << "\n";

        ROS_INFO("u=%.3f w=%.3f vL=%.3f vR=%.3f | x=%.3f y=%.3f yaw=%.3f",
                 S.u, S.w, S.vL, S.vR, S.x, S.y, S.yaw);
    };

    auto process = [&](const geometry_msgs::Pose& pose){
        const double now = ros::Time::now().toSec();
        S.dt = now - S.t_prev;
        S.t_prev = now;

        S.x = pose.position.x;
        S.y = pose.position.y;

        tf::Quaternion q(pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w);
        double roll, pitch;
        tf::Matrix3x3(q).getRPY(roll, pitch, S.yaw);

        if (!S.have_offset){
            S.ox = S.x; S.oy = S.y; S.have_offset = true;
            ROS_INFO("Offset gesetzt: (%.3f, %.3f)", S.ox, S.oy);
        }

        S.gio.setPose(S.x - S.ox, S.y - S.oy, S.yaw);

        if (!S.gio.getNextState(S.u, S.w, S.vL, S.vR, S.looped)){
            S.vL = 0; S.vR = 0;
            send();
            ROS_INFO("Pfad beendet");
            ros::shutdown();
            return;
        }
        send();
    };

    ros::Subscriber sub;
    if (use_amcl){
        sub = nh.subscribe<geometry_msgs::PoseWithCovarianceStamped>(
            "/amcl_pose", 10,
            [&](const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){ process(msg->pose.pose); });
        ROS_INFO("Control Node gestartet mit AMCL Pose");
    } else {
        sub = nh.subscribe<nav_msgs::Odometry>(
            "/odom", 10,
            [&](const nav_msgs::Odometry::ConstPtr& msg){ process(msg->pose.pose); });
        ROS_INFO("Control Node gestartet mit Odometrie Pose");
    }

    ros::spin();
    S.log.close();
    return 0;
}

