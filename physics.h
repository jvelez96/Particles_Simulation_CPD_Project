// physics.h
#include "grid.h"

void init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid);
double get_distance(Vector a, Vector b);
Vector get_force(Particle par, Grid grid, int add_x, int add_y);
Vector sum_forces(Vector *f);
void move_particle(long grid_sz, Particle *par, Grid **grid, long long id);


void showlist(std::list <int> g);
