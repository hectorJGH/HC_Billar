set title 'Billiard ball in stadium'
set xlabel 'x(t)'
set ylabel 'y(t)'
set samples 1000
set term pngcairo size 700, 500
set out 'billiard_graf.png'
unset key
plot 'billiard.txt' u 1:2 w lp lw 2
