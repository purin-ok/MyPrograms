set terminal postscript eps color
set out "sin.eps"
set datafile separator "\t"
set xrange [-2:102]
set xlabel "partition number"
set xtics (0, 20, 40, 60, 80, 100)
set yrange [-0.01:0.26]
set ylabel "error"
set ytics (0, 0.05, 0.1, 0.15, 0.2, 0.25)
set multiplot
set key at 100,0.25
plot 'sin.tsv' using 1:2 with points lt rgb 'red' smooth csplines title "trapezoid"
set key at 100,0.24
plot 'sin.tsv' using 3:4 with points lt rgb 'blue' smooth csplines title "simpson"
set key at 100,0.23
plot 'sin.tsv' using 5:6 with points lt rgb 'dark-green' smooth csplines title "romberg"
unset multiplot
set output
reset