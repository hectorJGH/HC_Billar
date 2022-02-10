g++ -fopenmp -O3  elipse_separation_time.cpp billiard.cpp billiard.h -o paral.x

parallel 'OMP_NUM_THREADS=11 ./paral.x 2>/dev//null' ::: 1.0 1.01 1.02 1.03 1.04 1.05 1.06 1.07 1.08 1.09 1.1
