set title sprintf("Billiard ball in eliptical stadium with alpha= %f /100.0", alpha)

set xlabel 'Time'
set ylabel 'Separation'
set samples 1000
set term pngcairo size 700, 500
set out sprintf("elipse_origin_separation_vs_time %f.png",alpha)
#set log y

set dummy t
Fexp(t) = A* exp(la *t)
A = 1E-5
la = 0.01
fit Fexp(t) archivo via A, la

plot archivo u 1:2 w lp pt 7 lc rgb 'red' t 'Data', Fexp(t) lw 3 lc rgb 'black' t sprintf("Fit with a Lyapunov exponent of %f", la)