set terminal postscript eps monochrome
set output 'res.eps'
set size nosquare 1,0.75
set xrange [1:25]
set yrange [-0.1:0.4]
set xlabel 'n'
set ylabel 'result'
#set xtics (0,"0.2" 200,"0.4" 400,"0.6" 600,"0.8" 800,"1.0" 1000)
#set style line 1 lt 2 lw 1 pt 5
set datafile separator ","
plot 'res.csv' u 1:2 t "trapezoid" w l ls 1 dt 2,'res.csv' u 1:3 t "simpson" w l ls 1 dt 3,'res.csv' u 1:4 t "romberg" w l ls 3 dt 4
set output
reset