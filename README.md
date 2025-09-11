    << How to start the Projekt >>($ stands for command line commands)

# Start the Robot
``` Ping the Bot to see if the connection to the LMS100 happend sucsesfully(Seperate Terminal)
$ping 192.168.0.51
```

```Enter the Catkin Workspace and execute the Volksbot launch file(Seperate Terminal)
$cd catkin_ws
$roslaunch volksbot messtechnikpraktikum.launch
```

```Execute the Joystick lunch file(Seperate Terminal)
 $roslaunch volksbot localjoystick.launch
```

# Start AMCL and Plotting
```Enter and executing the AMCL launch file
$cd catkin_ws/src/volksbot/launch/lehre/
$roslaunch messtechnikamcl.launch
```

```launch amcl_nodeGNU & odo_nodeGNUodo_nodeGNU with multi.launch to start recording the .txt for later plotting
$roslaunch my_first_project multi.launch
```
```start RVIZ to visulize changes in real time
$rviz
```

# Start the Path tracking Algorithm 

```Starting the Giovanni-Controller-Node with chosen Path(in this case acht.dat)
 $rosrun my_first_project gio_node /home/kian/Downloads/Beispielpfade/acht.dat
```

``` Creating a rosbag for further testing a validation
 $rosbag record -a
```

# After Code Execution

```Plotting the Odometry and AMCL Supported Path with GNU-Plot with a launch file(saved in my_first_project as multi.png)
$gnuplot multi.gp
``` 

```Playing the Rosbag for further validation
$rosparam set use_sim_time true
$rosbag play --clock nameofbag.bag
```
