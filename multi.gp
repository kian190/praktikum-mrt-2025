set size ratio -1
set terminal pngcairo size 1600,600   
set output 'multi.png'

set multiplot layout 1,4 title "Pfadvergleich" font ",14"

# --- AMCL ---
set size ratio -1
set title 'Amcl-Pfad'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'amcl_path.txt' using 1:2 with linespoints lc rgb "violet" title 'AMCL'

# --- Odometrie ---
set title 'Odometrie-Pfad'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
plot 'odom_path.txt' using 1:2 with linespoints lc rgb "blue" title 'Odometrie'

# --- Giovani ---
set title 'Giovani-Pfad'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
set xrange [-3:3]
set yrange [-3:3]
plot '/home/kian/Downloads/Beispielpfade/giodat.txt' using 1:2 with linespoints lc rgb "orange" title 'Giovani-Pfad'

# --- Roh ---
set title 'Roh-Daten'
set xlabel 'x [m]'
set ylabel 'y [m]'
set grid
set xrange [-3:3]
set yrange [-3:3]
plot '/home/kian/Downloads/Beispielpfade/acht.dat' using 1:2 with linespoints lc rgb "green" title 'Roh-Daten'
unset multiplot
