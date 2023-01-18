set xtics (0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0)
set ytics (0, 20, 40, 60, 80, 100, 120)
set xlabel "x"
set ylabel "y"
set xrange [0:4.5]
set yrange [-5:120]
set key off
set terminal postscript eps monochrome
set output 'main.eps'
set nokey
plot 2*exp(x), 'main.txt' using 1:2 pt 7
set output
reset