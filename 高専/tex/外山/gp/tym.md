# 外山レポのデータ

sin(t)+sin(100t)

```gnuplot {cmd=true hide=true output="html"}
set terminal svg
l "sin1_100.gp"
```

sin(t)+20sin(100t)

```gnuplot {cmd=true hide=true output="html"}
set terminal svg
l "sin1_20-100.gp"
```

ibuki1

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
l "ibuki1.gp"
```

ibuki2

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
l "ibuki2.gp"
```

ibuki3

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
l "ibuki3.gp"
```

ibuki4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
l "ibuki4.gp"
```

ibuki4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
l "ibuki4.gp"
```

kanako1

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/kanako1.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/kanako1_folse_spe.csv' u 1:2 t "kanako1" w l ls 1
 set output
 reset
```

kanako2

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/kanako2.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/kanako2_true_spe.csv' u 1:2 t "kanako1" w l ls 1
 set output
 reset
```

kanako3

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/kanako3.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/kanako3_folse_spe.csv' u 1:2 t "kanako3" w l ls 1
 set output
 reset
```

kanako4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/kanako4.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/kanako4_true_spe.csv' u 1:2 t "kanako4" w l ls 1
 set output
 reset
```

yosuke1

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yosuke1.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yosuke1_folse_spe.csv' u 1:2 t "yosuke1" w l ls 1
 set output
 reset
```

yosuke2

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yosuke2.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yosuke2_true_spe.csv' u 1:2 t "yosuke2" w l ls 1
 set output
 reset
```

yosuke3

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yosuke3.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yosuke3_folse_spe.csv' u 1:2 t "yosuke3" w l ls 1
 set output
 reset
```

yosuke4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yosuke4.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yosuke4_true_spe.csv' u 1:2 t "yosuke4" w l ls 1
 set output
 reset
```

yuuka1

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yuuka1.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yuuka1_folse_spe.csv' u 1:2 t "yuuka1" w l ls 1
 set output
 reset
```

yuuka2

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
 set output "../img/yuuka2.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yuuka2_true_spe.csv' u 1:2 t "yuuka2" w l ls 1
 set output
 reset
```

yuuka3

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yuuka3.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yuuka3_folse_spe.csv' u 1:2 t "yuuka3" w l ls 1
 set output
 reset
```

yuuka4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/yuuka4.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/yuuka4_true_spe.csv' u 1:2 t "yuuka4" w l ls 1
 set output
 reset
```

hisyo1

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/hisyo1.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/hisyo1_folse_spe.csv' u 1:2 t "hisyo1" w l ls 1
 set output
 reset
```

hisyo2

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/hisyo2.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/hisyo2_true_spe.csv' u 1:2 t "hisyo2" w l ls 1
 set output
 reset
```

hisyo3

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/hisyo3.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/hisyo3_folse_spe.csv' u 1:2 t "hisyo3" w l ls 1
 set output
 reset
```

hisyo4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/hisyo4.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/hisyo4_true_spe.csv' u 1:2 t "hisyo4" w l ls 1
 set output
 reset
```

keigo1

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/keigo1.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/keigo1_folse_spe.csv' u 1:2 t "keigo1" w l ls 1
 set output
 reset
```

keigo2

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/keigo2.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/keigo2_true_spe.csv' u 1:2 t "keigo2" w l ls 1
 set output
 reset
```

keigo3

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/keigo3.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/keigo3_folse_spe.csv' u 1:2 t "keigo3" w l ls 1
 set output
 reset
```

keigo4

```gnuplot {cmd=true hide=true output="html"}
# set terminal svg
set terminal postscript eps monochrome
set output "../img/keigo4.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'Strength'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/keigo4_true_spe.csv' u 1:2 t "keigo4" w l ls 1
 set output
 reset
```

result

```gnuplot {cmd=true output="html"}
set terminal svg
# set terminal postscript eps monochrome
# set output "../img/result.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'speed'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/1result.csv' u 1:2 t "false" pointtype 6,'../csv/1result.csv' u 3:4 t "true" pointtype 3
 set output
 reset
```

result

```gnuplot {cmd=true output="html"}
#set terminal svg
set terminal postscript eps monochrome
set output "../img/result.eps"
set size nosquare 1,0.75
#  set yrange [-0.5:7]
   set xlabel 'Amplitude[Hz]'
 set ylabel 'speed'
set xzeroaxis lt 1 lw 1
set style line 2 lt 2 lw 1 pt 5
set datafile separator ","
# set term wxt
plot '../csv/1result.csv' u 1:2 t "false" pointtype 6,'../csv/1result.csv' u 3:4 t "true" pointtype 3
 set output
 reset
```
