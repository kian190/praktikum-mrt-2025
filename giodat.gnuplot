
#heheheha
set terminal pngcairo size 800,600
set output 'giodat.png'
set title 'giodat-Pfad'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'giodat.txt' using 1:2 with linespoints title 'Pfad'
