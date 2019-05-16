// grid.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <mpi.h>
#define BILLION 1E9


typedef struct VectorStruct {
    double x;
    double y;
} Vector;

typedef struct ParticleStruct {
    Vector pos;
    Vector v;
    double m;
} Particle;

typedef struct GridStruct {
    Vector center;
    double M;
    double Mnext;
} Grid;

int cell_id(int x, int y, int grid_sz);
Grid **init_grid(long size);
void clear_grid(long size, Grid **grid);
void swap_grid_Ms (long size, Grid **grid);
void update_center_all(long long part_no, long size, Grid **grid, Particle *par);
void overall_center(Particle *par, long long part_no, double totalM);
void free_all(Particle *par, Grid  **grid, long grid_sz);
