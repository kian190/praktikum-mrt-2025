#include <fstream>
#include <ros/ros.h>
#include "my_first_project/gio_path.h"
#include <volksbot/vels.h>  // rostopic  info /Vel

std::ofstream giodat;

int main(int argc, char **argv) {
    ros::init(argc, argv, "gio_node");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<volksbot::vels>("/Vel", 10);// mit 

    giodat.open("/home/kian/Downloads/Beispielpfade/giodat.txt");
    if (!giodat.is_open()) {
        ROS_ERROR("Konnte odom_path.txt nicht oeffnen!");
        return 1;
    }else if (giodat.is_open()){
        ROS_INFO("Konnte Connecten G");
    }

    CGioController controller;
    controller.setPose(0.0, 0.0, 0.0);

    if (argc > 1) {
        std::string pathFile = argv[1];
        if (!controller.getPathFromFile(pathFile.c_str())) {
            ROS_ERROR("Fehler beim Laden der Pfaddatei: %s", pathFile.c_str());
            return -1;
        }
        ROS_INFO("Pfad erfolgreich geladen: %s", pathFile.c_str());
    } else {
        ROS_ERROR("Pfad NICHT erfolgreich geladen");
        return -1;
    }

    double x=0.0, y=0.0, phi=0.0;
    ros::Rate loop(10);
    double dt = 0.1; // 10 Hz

    volksbot::vels vel_msg;
    while (ros::ok()) {
        double u, w, vleft, vright;

        if (controller.getNextState(u, w, vleft, vright, 0)) {
            ROS_INFO("u=%f, w=%f, vL=%f, vR=%f", u, w, vleft, vright);

            //"Standart" differential drive modell
            x   += u * cos(phi) * dt; 
            y   += u * sin(phi) * dt;
            phi += w * dt;

            double factor = -83; //tuning tha bish
            vel_msg.left  = vleft * factor;//(vleft*-15);
            vel_msg.right = vright * factor;//(vright*-15);
            vel_msg.id    = 0;
            vel_pub.publish(vel_msg);

            controller.setPose(x, y, phi);  // <-- neue Pose 
        }else{
            ROS_INFO("Pfad beendet - sende finalen Stop-Befehl");
            vel_msg.left = 0;
            vel_msg.right = 0;
            vel_msg.id = 0;
            vel_pub.publish(vel_msg);
            ros::spinOnce();
            ros::Duration(0.2).sleep(); 
            break;// break sollte genug sein
        }
        giodat << x << " " << y << " " << std::endl;
        ros::spinOnce();
        loop.sleep();
    }
    ROS_INFO("giodat.close");
    giodat.close();

    return 0; 
}
