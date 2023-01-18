set terminal postscript eps color
set output "yy.eps"
set datafile separator ","
set xrange [-0.1:2.1]
set xlabel ""
set xtics (0, 0.25, 0.50, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0)
set yrange [-0.5:7.7]
set ylabel ""
set ytics (0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0)
set multiplot
set key at 0.55,7.4
plot 'aa20.csv' using 1:2 with points lt rgb 'red' smooth csplines title "20"
set key at 0.55,7.1
plot 'aa50.csv' using 1:2 with points lt rgb 'blue' smooth csplines title "50"
set key at 0.55,6.8
plot 'aa100.csv' using 1:2 with points lt rgb 'dark-green' smooth csplines title "100"
set key at 0.55,6.5
plot 'aa200.csv' using 1:2 with points lt rgb 'green' smooth csplines title "200"
set key at 0.55,6.2
plot 'ex2.csv' using 1:2 with points lt rgb 'black' smooth csplines title "theoretical valu"
unset multiplot
set output
resetet