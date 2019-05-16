// grid.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <mpi.h>
#define BILLION 1E9
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))


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
void update_center_local(long long part_no, long size, Grid **grid, Particle *par);
void overall_center_local(Particle *par, Grid **grid, long long part_no, double totalM);
void broadcast_mass_centers(Grid **grid, int p_rank, int n_pr, long grid_sz);
void broadcast_mass(Grid **grid, int p_rank, int n_pr, long grid_sz);
void broadcast_overall_center(Grid **grid, int p_rank, int n_pr, double *x, double *y);
void broadcast_totalM(int p_rank, int n_pr, double *totalM);
void free_all(Particle *par, Grid  **grid, long grid_sz, int *par_block, double *par_buffer);
