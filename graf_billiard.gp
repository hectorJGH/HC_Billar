set title 'Billiard ball in stadium'
set xlabel 'x(t)'
set ylabel 'y(t)'
set samples 1000
f(x)=sqrt(1-x**2)+0.01
g(x)=-sqrt(1-x**2)
set term pngcairo size 700, 500
set out 'billiard_graf.png'
unset key
plot 'billiard.txt' u 1:2 w lp lw 2,f(x),g(x)
