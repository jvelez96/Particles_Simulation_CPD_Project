// physics.h
#include "grid.h"

long double get_distance(long double x1, long double y1, long double x2, long double y2);
void showlist(std::list <int> g);
void init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid);
void move_particle(long ncside, Particle par, Grid **grid);
