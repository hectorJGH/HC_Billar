set title 'Billiard ball in stadium'
set xlabel 'separation'
set ylabel 'time'
set samples 1000
set term pngcairo size 700, 500
set out 'separation_vs_time.png'
#set log y

set dummy t
Fexp(t) = A* exp(la *t)
A = 1E-5
la = 0.01
fit Fexp(t) 'separation.txt' via A, la

plot 'separation.txt' u 1:2 w lp pt 7 lc rgb 'red' t 'Data', Fexp(t) lw 3 lc rgb 'black' t 'Least squares fit'