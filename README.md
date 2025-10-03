
# Startup Procedure
('$' steht für die Shell; jede Anweisung in einem eigenen Terminal)

## Start the Robot
Ping den Bot, um die Verbindung zum LMS100 zu prüfen
$ ping 192.168.0.51

Catkin-Workspace öffnen und Volksbot starten
$ cd ~/catkin_ws
$ roslaunch volksbot messtechnikpraktikum.launch

Lokale Joystick-Steuerung starten
$ roslaunch volksbot localjoystick.launch

## Start AMCL und Plotting
AMCL starten
$ cd ~/catkin_ws/src/volksbot/launch/lehre/
$ roslaunch messtechnikamcl.launch

amcl_nodeGNU und odo_nodeGNU starten (schreibt amcl_path.txt und odom_path.txt)
$ roslaunch my_first_project multi.launch

RViz öffnen
$ rviz

## Start the Path tracking Algorithm
Giovanni-Controller starten (Pfad ist in /src/gio_node.cpp hardcodiert)
$ rosrun my_first_project gio_node

## Optional: Rosbag
Alle Topics mitschneiden
$ rosbag record -a
(-a: all topics)

## After Code Execution
Mit Gnuplot plotten (erzeugt multi.png)
$ gnuplot multi.gp

Rosbag-Replay
$ rosparam set use_sim_time true
(Nodes nutzen Simulationszeit)

$ rosbag play --clock NameOfBag.bag
(--clock veröffentlicht /clock während des Replays)

## Kurzprozess: Pfadtracking und Vergleich (Details in savedPaths/ReadMe.txt)
1. Pfad mit Odometrie-Regler fahren:
   $ rosrun my_first_project gio_node
   (ohne Flags; nutzt den im Code hinterlegten Pfad)
2. amcl_path.txt und odom_path.txt nach savedPaths/ kopieren.
3. In savedPaths/ umbenennen in:
   Odomamcl_path.txt und Odomodom_path.txt.
4. Plot erstellen:
   $ gnuplot AvOStacked.gnuplot
   (erzeugt AvOStacked.png, direkter Vergleich)
   Alternativ:
   $ gnuplot AvOoverlay.gnuplot
   (Overlay/Side-by-Side)

Hinweis: Der ausführliche Vergleichsablauf steht in savedPaths/ReadMe.txt und wird hier nur kurz referenziert.
``
