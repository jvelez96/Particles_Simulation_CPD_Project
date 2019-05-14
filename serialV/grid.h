// grid.h
#include "LinkedList.h"

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
    LinkedList *par_list;
} Grid;

Grid **init_grid(long size);
void clear_grid(long size, Grid **grid);
void swap_grid_Ms (long size, Grid **grid);
void update_center_one(Particle *par, Grid *grid);
void update_center_all(long size, Grid **grid, Particle *par);
void overall_center(Particle *par, long long part_no, double totalM);
void free_all(Particle *par, Grid  **grid, long grid_sz);
