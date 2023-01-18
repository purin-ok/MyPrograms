set terminal postscript eps color
set output "y.eps"
set datafile separator ","
set xrange [-0.1:2.1]
set xlabel "t"
set xtics (0, 0.25, 0.50, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0)
set yrange [0.9:2.1]
set ylabel ""
set ytics (1.0, 1.2, 1.4, 1.6, 1.8, 2.0)
set multiplot
set key at 2,2.05
plot 'a20.csv' using 1:3 with points lt rgb 'red' smooth csplines title "20"
set key at 2,2
plot 'a50.csv' using 1:3 with points lt rgb 'blue' smooth csplines title "50"
set key at 2,1.95
plot 'a100.csv' using 1:3 with points lt rgb 'dark-green' smooth csplines title "100"
set key at 2,1.9
plot 'a200.csv' using 1:3 with points lt rgb 'green' smooth csplines title "200"
set key at 2,1.85
plot 'ex.csv' using 1:3 with points lt rgb 'black' smooth csplines title "theoretical value"
unset multiplot
set output
reset