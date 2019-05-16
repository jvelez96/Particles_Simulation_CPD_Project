//main.c
#include "physics.h"


int main (int argc, char* argv[]) {
  int i, j;
  int p_rank, n_pr;
  int *par_block;
  int rem;
  int a;
  long seed, grid_sz, steps;
  long long part_no;
  double totalM;
  MPI_Status status;
  int pr_part_no;
  struct timespec requestStart, requestEnd, moveStart, moveEnd;

  MPI_Init (&argc, &argv);

  MPI_Comm_rank (MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &n_pr);

  if (argc!=5){
    printf("Incorrect number of arguments.\n");
    MPI_Finalize();
    exit(1);
  }

  seed = atoi(argv[1]);
  grid_sz = atoi(argv[2]);
  part_no = atoi(argv[3]);
  steps = atoi(argv[4]);

  par_block = malloc(sizeof(int)* n_pr);
  rem = part_no % n_pr;

  divide_par(n_pr, part_no, rem, par_block);

  /*
  printf("Seed nº: %ld\n", *seed);
  printf("Grid size: %ld\n", grid_sz);
  printf("Nº of particles: %lld\n", part_no);
  printf("Nº of steps: %ld\n", steps);*/

  //Start both structures

  Grid **grid = NULL;
  Particle *par = NULL;

  grid = init_grid(grid_sz);

  pr_part_no = get_par_number(part_no, par_block, n_rank,n_pr)
  par = (Particle*) malloc(sizeof(Particle) * pr_part_no);
  if(p_rank == 0)
    totalM = init_particles(seed,grid_sz,part_no,par, grid, par_block);

  clock_gettime(CLOCK_REALTIME, &requestStart);
  /* ciclo baseado no numero de steps */
  for(i=0; i<steps; i++){
    update_center_all(part_no, grid_sz, grid, par);
    clear_grid(grid_sz, grid);

    #pragma omp parallel
        {
          /* 2.1. PROCESS ELEMENTS */
          #pragma omp for private (j)
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
  MPI_Finalize();
  return 0;

}
