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

Grid **init_grid(int size);
void clear_grid(int size, Grid **grid);
void swap_grid_Ms (int size, Grid **grid);
void update_center_one(Particle *par, Grid *grid);
void update_center_all(int size, Grid **grid, Particle *par);
void overall_center(Particle *par, long long part_no, double totalM);
