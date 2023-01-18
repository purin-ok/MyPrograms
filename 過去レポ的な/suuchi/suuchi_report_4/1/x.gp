set terminal postscript eps monochrome
set output 'x(t).eps'
#set size nosquare 1,0.75
set xrange [0:2]
set yrange [0.9:2.2]
set xlabel 't'
set ylabel 'x(t)'
#set xtics (0,"0.2" 200,"0.4" 400,"0.6" 600,"0.8" 800,"1.0" 1000)
set style line 1 lt 2 lw 1 pt 5
set datafile separator ","
plot 'out10.csv' u 1:4 t "x(t)" w l ls 2 dt 1 ,'out5.csv' u 1:2 t "N=5" w l ls 1 dt 2,'out10.csv' u 1:2 t "N=10" w l ls 5 dt 3,'out20.csv' u 1:2 t "N=20" w l ls 3 dt 4
set output
reset