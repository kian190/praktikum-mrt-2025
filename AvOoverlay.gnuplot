
set terminal pngcairo size 1600,600   
set output 'AvOoverlay.png'

set multiplot layout 1,4 title "Amcl-Regeler und Odometrie-Regeler Vegleich" font ",14"

set size noratio

# --- AMCL ---
set title 'Amcl-Pfad mit Amcl-Regelung'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'amcl_path.txt' with lines lc rgb "violet" title 'AMCL'



# --- Odometrie ---
set title 'Odometrie-Pfad mit Amcl-Regelung'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
#plot 'odom_path.txt' using 1:2 with lines lc rgb "blue" title 'Odometrie'
angle = -51
theta = angle*pi/180
dx = +0.1
dy = -0.36
plot 'odom_path.txt' using (cos(theta)*$1 + sin(theta)*$2 + dx):( -sin(theta)*$1 + cos(theta)*$2 + dy ) \
     with lines lc rgb "blue" title 'Odometrie'

# --- AMCL ---
set title 'Amcl-Pfad mit Odometrie-Regeler'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
angle = 52
theta = angle*pi/180
dx = 0.25
dy = -0.5
#plot 'amcl_path.txt' using (cos(theta)*$1 + sin(theta)*$2 + dx):( -sin(theta)*$1 + cos(theta)*$2 + dy ) \
#     with lines lc rgb "violet" title 'AMCL'
plot 'savedPaths/Odomamcl_path.txt' using  (cos(theta)*$1 + sin(theta)*$2 + dx):( -sin(theta)*$1 + cos(theta)*$2 + dy ) \
with lines lc rgb "green" title 'AMCL'

set title 'Odometrie-Pfad mit Odometrie-Regeler'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'savedPaths/Odomodom_path.txt' using 1:2 with lines lc rgb "red" title 'Odometrie'
#angle = -50
#theta = angle*pi/180
#dx = 0.2
#dy = -0.5
#plot 'odom_path.txt' using (cos(theta)*$1 + sin(theta)*$2 + dx):( -sin(theta)*$1 + cos(theta)*$2 + dy ) \
#0     with lines lc rgb "blue" title 'Odometrie'

unset multiplot
