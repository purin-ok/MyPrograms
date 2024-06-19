set terminal postscript eps monochrome
set output "../img/ibuki2.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/ibuki2_true_spe.csv' u 1:2 t "ibuki2" w l ls 1  
 set output 
 reset