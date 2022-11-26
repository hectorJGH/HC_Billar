set title 'Lyapunov exponent vs alpha in eliptical stadium (start at the origin)'
set xlabel '{/Symbol a}'
set ylabel 'Lyapunov exponent {/Symbol l}'
set samples 1000
set term pngcairo size 700, 900
set out 'exponent_alpha_elipse_origin.png'
unset key

#set dummy alfa
#Ly(alfa) = m * alfa + b
#m = 0.0032
#b = 0.0005

#fit Ly(alfa) 'exponentes_elipse.ttxt' via m, b

plot 'exponentes_elipse_centro.ttxt' u 1:2 w lp pt 7 lc rgb 'black' t 'Data'#, Ly(alfa) lw 3 lc rgb 'red' t sprintf("Fit with a slope of %f", m)