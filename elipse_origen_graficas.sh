parallel 'OMP_NUM_THREADS=12 ./elipse_separation_time.x {} 0.0 2>/dev//null' ::: 1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0
gp() {
  OMP_NUM_THREADS=11 gnuplot -e 'alpha='"$1"'; archivo="'"$1"'elipse.txt"' graf_elipse_origin_separation_time.gp
}
export -f gp
parallel gp {} ::: 100 150 200 250 300 350 400 450 500
