# Startup Procedure
('$' stands for the command line) & (every instruction in a different Terminal)

## Start the Robot
Ping the bot to check if the connection to the LMS100 has been established successfully
```
$ping 192.168.0.51
```

Enter the Catkin workspace and execute the Volksbot launch file
```
$cd catkin_ws
$roslaunch volksbot messtechnikpraktikum.launch
```

Enter the Catkin Workspace and execute the Volksbot launch file
```
 $roslaunch volksbot localjoystick.launch
```

## Start AMCL and Plotting
Execute the AMCL launch file
```
$cd catkin_ws/src/volksbot/launch/lehre/
$roslaunch messtechnikamcl.launch
```

Launch amcl_nodeGNU and odo_nodeGNU with multi.launch to start recording the .txt files for later plotting
```
$roslaunch my_first_project multi.launch
```
Start RViz to visualize changes in real time
```
$rviz
```

## Start the Path tracking Algorithm 

Start the Giovanni controller node with a chosen path (in this case acht.dat)
```
 $rosrun my_first_project gio_node /home/kian/Downloads/Beispielpfade/acht.dat
```

Create a rosbag for further testing and validation
```
 $rosbag record -a
```

## After Code Execution

Plot the odometry and the AMCL-supported path with Gnuplot using a launch file (saved in my_first_project as multi.png)
```
$gnuplot multi.gp
``` 

Replay the rosbag for further validation
```
$rosparam set use_sim_time true
$rosbag play --clock NameOfBag.bag
```
