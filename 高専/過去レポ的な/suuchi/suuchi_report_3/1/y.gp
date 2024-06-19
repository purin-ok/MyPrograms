set terminal postscript eps monochrome
set output 'res.eps'
set size nosquare 1,0.75
set xrange [0:4]
set yrange [0:120]
set xlabel 'x'
set ylabel 'y'
#set xtics (0,"0.2" 200,"0.4" 400,"0.6" 600,"0.8" 800,"1.0" 1000)
#set style line 1 lt 2 lw 1 pt 5
set datafile separator ","
plot 'res.csv' u 1:2 t ""w l ls 1 dt 2
set output
reset