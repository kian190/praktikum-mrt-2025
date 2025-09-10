set terminal pngcairo size 800,600
set output 'odom_path.png'
set title 'Odometrie-Pfad'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'odom_path.txt' using 1:2 with linespoints title 'Pfad'
