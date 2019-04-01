// physics.h
#include "grid.h"

void init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid);
long double get_distance(Vector a, Vector b);
Vector get_force(Particle par, Grid grid);
void move_particle(long ncside, Particle par, Grid **grid, long long id);


void showlist(std::list <int> g);
