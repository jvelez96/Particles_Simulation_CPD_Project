// main.cpp
#include "physics.h"

int main (int argc, char* argv[]) {
  int i;
  int a;
  int seed, grid_sz, part_no, steps;

  if (argc!=5){
    std::cout << "Incorrect number of arguments." << std::endl;
    exit(1);
  }

  std::istringstream iss( argv[1] );
  if (iss >> seed){
      std::cout << "Seed nº:" << seed << std::endl;
  }

  std::istringstream iss1( argv[2] );
  if (iss1 >> grid_sz){
      std::cout << "Grid size:" << grid_sz << std::endl;
  }

  std::istringstream iss2( argv[3] );
  if (iss2 >> part_no){
      std::cout << "Nº of particles:"<< part_no << std::endl;
  }

  std::istringstream iss3( argv[4] );
  if (iss3 >> steps){
      std::cout << "Nº of steps:" << steps << std::endl;
  }

  //Start both structures
  Grid **grid = new Grid*[grid_sz];
  for(i=0;i<grid_sz;i++){
    grid[i] = new Grid[grid_sz];
  }
  Particle par[part_no];

  init_grid(grid_sz, grid);
  init_particles(seed,grid_sz,part_no,par, grid);

  /* ciclo baseado no numero de steps */
  for(i=0; i<steps; i++){
    update_center_all(grid_sz, grid, par);

    //calcular as forças
    //calcular novas velocidades e posiçoes
    clear_grid(grid_sz, grid);
  }



  return 0;
}
