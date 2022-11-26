set title 'Billiard ball in eliptical stadium'
set xlabel 'x(t)'
set ylabel 'y(t)'
set yrange [-1.01:1.01]
set samples 1000
f(x)=1.01*sqrt(1-x**2)
g(x)=-f(x)
set term pngcairo size 900, 900
set out 'elipse_billiard_graf.png'
unset key
plot 'elipse_billiard.txt' u 1:2 w lp lw 2,f(x),g(x)