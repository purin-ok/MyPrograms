set terminal postscript eps color
set output "e.eps"
set datafile separator "\t"
set xrange [-2:102]
set xlabel "partition number"
set xtics (0, 20, 40, 60, 80, 100)
set yrange [-0.1:3]
set ylabel "error"
set ytics (0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0)
set multiplot
set key at 100,2.9
plot 'e.tsv' using 1:2 with points lt rgb 'red' smooth csplines title "trapezoid"
set key at 100,2.8
plot 'e.tsv' using 3:4 with points lt rgb 'blue' smooth csplines title "simpson"
set key at 100,2.7
plot 'e.tsv' using 5:6 with points lt rgb 'dark-green' smooth csplines title "romberg"
unset multiplot
set output
reset