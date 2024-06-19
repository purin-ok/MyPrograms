set terminal postscript eps monochrome
set output 'y(t).eps'
#set size nosquare 1,0.75
set xrange [0:2]
set yrange [0.1:8]
set xlabel 'x'
set ylabel 'y(x)'
#set xtics (0,"0.2" 200,"0.4" 400,"0.6" 600,"0.8" 800,"1.0" 1000)
#set style line 1 lt 2 lw 1 pt 5
set datafile separator ","
plot '50.csv' u 1:4 t "y(x)" w l ls 2 dt 1 ,'5.csv' u 1:2 t "N=5" w l ls 1 dt 2,'10.csv' u 1:2 t "N=10" w l ls 1 dt 3,'20.csv' u 1:2 t "N=20" w l ls 3 dt 4
set output
reset