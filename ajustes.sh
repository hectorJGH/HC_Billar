parallel 'OMP_NUM_THREADS=11 ./separation_time.x 2>/dev//null' ::: 0.0 0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1
gp() {
  OMP_NUM_THREADS=11 gnuplot -e 'alpha='"$1"'; archivo="'"$1"'.txt"' graf_separation_time.gp
}
export -f gp
parallel gp {} ::: 0 1 2 3 4 5 6 7 8 9 10
