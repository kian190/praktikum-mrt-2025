# test
set terminal pngcairo size 800,600
set output 'amcl_path.png'
set title 'Amcl-Pfad'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'amcl_path.txt' using 1:2 with linespoints title 'Pfad'
