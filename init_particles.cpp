#define RND0_1 ((double) random() / ((long long)1<<31))
#define G 6.67408e-11
#define EPSLON 0.01
#include "grid.h"


void init_particles(long seed, long ncside, long long n_part, Particle *par){
  long long i;

  srandom(seed);

  for(i = 0; i < n_part; i++)
  {
    par[i].setX(RND0_1);
    par[i].setY(RND0_1);
    par[i].setVX(RND0_1 / ncside / 10.0);
    par[i].setVY(RND0_1 / ncside / 10.0);
    par[i].setM( RND0_1 * ncside / (G * 1e6 * n_part)) ;
    std::cout << "X: " << par[i].getX() << std::endl;
    std::cout << "Y: " << par[i].getY() << std::endl;
    std::cout << "VX: " << par[i].getVX() << std::endl;
    std::cout << "VY: " << par[i].getVY() << std::endl;
    std::cout << "M: " << par[i].getM() << std::endl;
    std::cout << "\n";
  }
}

void init_grid(int size, Grid **grid){
  long long i, j;
  for(i=0; i< size;i++){
    for(j=0;j<size;j++){
      grid[i][j].setX(i);
      grid[i][j].setY(j);
    }
  }
}
