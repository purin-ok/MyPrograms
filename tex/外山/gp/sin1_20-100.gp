# set terminal postscript eps monochrome
# set output "../img/1_20-100.eps"
set size nosquare 1,0.75
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
#  set yrange [-0.5:7]
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot 'D:/MyPrograms/自分用/ty/sin_1.csv' u 1:2 t "sin(t)+20sin(100t)" w l ls 1  
# set output
# reset