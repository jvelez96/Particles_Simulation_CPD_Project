mpicc -g simpar.c grid.c physics.c -fopenmp -lm -o simpar
set OMP_NUM_THREADS=8
