gcc simpar-omp.c grid.c physics.c LinkedList.c -fopenmp -lm -o simpar-omp
set OMP_NUM_THREADS=8
