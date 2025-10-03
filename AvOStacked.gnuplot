set size ratio -1
set terminal pngcairo size 1600,600   
set output 'AcOStacked.png'

set title 'Amcl-Regeler und Odometrie-Regeler Vegleich'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
#set key outside top 
set key at graph 1.8,1

a1_angle = 52 #Amcl with Odom-Regler
a1_theta = a1_angle*pi/180
a1_dx = 0.25
a1_dy = -0.5

a2_angle = -51 #Odometrie mit Amcl-Regelung
a2_theta = a2_angle*pi/180
a2_dx = 0.1
a2_dy = -0.36

plot \
 'amcl_path.txt' with lines lc rgb "violet" title 'AMCL mit Amcl-Regelung',\
 'savedPaths/Odomamcl_path.txt' using (cos(a1_theta)*$1 + sin(a1_theta)*$2 + a1_dx):(-sin(a1_theta)*$1 + cos(a1_theta)*$2 + a1_dy) \
     with lines lc rgb "green" title 'Amcl mit Odometrie-Regelung',\
 'odom_path.txt' using (cos(a2_theta)*$1 + sin(a2_theta)*$2 + a2_dx):(-sin(a2_theta)*$1 + cos(a2_theta)*$2 + a2_dy) \
     with lines lc rgb "blue" title 'Odometrie mit Amcl-Regelung',\
 'savedPaths/Odomodom_path.txt' using 1:2 with lines lc rgb "red" title 'Odometrie mit Odometrie-Regelung'
