# 
# Startup Procedure
('$' stands for the shell; each instruction in a separate terminal)

## Start the Robot
Ping the bot to verify the LMS100 connection
```
$ ping 192.168.0.51
```

Open the catkin workspace and launch the Volksbot
```
$ cd ~/catkin_ws
```
```
$ source devel/setup.bash
```
```
$ roslaunch volksbot messtechnikpraktikum.launch
```

Start joystick control
```
$ roslaunch volksbot localjoystick.launch
```

## Start AMCL and Plotting
Start AMCL
```
$ cd ~/catkin_ws/src/volksbot/launch/lehre/
```
```
$ roslaunch messtechnikamcl.launch
```

Open RViz
```
$ rviz
```

Start multi plot logging (writes position data to amcl_path.txt and odom_path.txt)
```
$ roslaunch my_first_project multi.launch
```

## Path tracking and comparison 

1. Drive the path with the odometry controller:
```
$ rosrun my_first_project gio_node
```
   (without flags to use odometry in the Giovanni Controller)
   (the path is hardcoded in /src/gio_node.cpp and can be changed there)

2. Copy amcl_path.txt and odom_path.txt into savedPaths/.

3. In savedPaths/ rename them to:
   Odomamcl_path.txt and Odomodom_path.txt.

4. Drive the path with the AMCL controller:
```
$ rosrun my_first_project gio_node --use-amcl
```
   (--use-amcl switches the controller to AMCL input instead of /odom)

5. Create the plots:
$ gnuplot AvOStacked.gnuplot
   (creates AvOStacked.png, stacked comparison)
$ gnuplot AvOoverlay.gnuplot
   (creates AvOoverlay.png, side-by-side comparison)

Note: The full comparison procedure is in savedPaths/ReadMe.txt and is only referenced here.
e: The full comparison procedure is in savedPaths/ReadMe.txt and is only referenced here.
