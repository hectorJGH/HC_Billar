g++ -fopenmp -O3  separation_time.cpp billiard.cpp billiard.h -o paral.x

parallel 'OMP_NUM_THREADS=11 ./paral.x 2>/dev//null' ::: 0.0 0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1