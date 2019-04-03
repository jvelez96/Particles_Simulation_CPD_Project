//main.c
#include "physics.h"

int main (int argc, char* argv[]) {
  int i, j;
  int a;
  long seed, grid_sz, steps;
  long long part_no;
  double totalM;
  struct timespec requestStart, requestEnd, moveStart, moveEnd;

  if (argc!=5){
    printf("Incorrect number of arguments.\n");
    exit(1);
  }

  seed = atoi(argv[1]);
  grid_sz = atoi(argv[2]);
  part_no = atoi(argv[3]);
  steps = atoi(argv[4]);

  /*
  printf("Seed nº: %ld\n", *seed);
  printf("Grid size: %ld\n", grid_sz);
  printf("Nº of particles: %lld\n", part_no);
  printf("Nº of steps: %ld\n", steps);*/

  //Start both structures
  Grid **grid = NULL;
  Particle *par = NULL;

  grid = init_grid(grid_sz);
  par = (Particle*) malloc(sizeof(Particle) * part_no);
  totalM = init_particles(seed,grid_sz,part_no,par, grid);

  clock_gettime(CLOCK_REALTIME, &requestStart);
  /* ciclo baseado no numero de steps */
  for(i=0; i<steps; i++){
    update_center_all(grid_sz, grid, par);
    clear_grid(grid_sz, grid);

    #pragma omp parallel
        {
          /* 2.1. PROCESS ELEMENTS */
          #pragma omp for
          for(j=0; j<part_no; j++){
              move_particle(grid_sz, &par[j], grid, j);
          }
        }
    swap_grid_Ms(grid_sz, grid);
  }

  printf("%.2f %.2f\n", par[0].pos.x, par[0].pos.y);
  overall_center(par, part_no, totalM);
  free_all(par, grid, grid_sz); //Frees all memory

  clock_gettime(CLOCK_REALTIME, &requestEnd);
  // Calculate time it took
  double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
    + ( requestEnd.tv_nsec - requestStart.tv_nsec )
    / BILLION;
  printf( "It took: %lfs\n", accum);
  return 0;

}
