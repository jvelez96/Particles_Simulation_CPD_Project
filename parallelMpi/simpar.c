//main.c
#include "physics.h"

int main (int argc, char* argv[]) {
  int i, j;
  int p_rank, n_pr;
  int *par_block;
  int rem;
  int a;
  long seed, grid_sz, steps;
  long long part_no, pr_part_no;
  long long aux_i=0;
  double totalM;
  MPI_Status status;
  struct timespec requestStart, requestEnd, moveStart, moveEnd;
  double *par_buffer = NULL;

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

  //Start both structures

  Grid **grid = NULL;
  Particle *par = NULL;

  grid = init_grid(grid_sz);

  pr_part_no = get_par_number(part_no, par_block, p_rank,n_pr);
  printf("Process: %d   part: %lld\n", p_rank, pr_part_no);
  par = (Particle*) malloc(sizeof(Particle) * pr_part_no);
  if(p_rank == 0){
    totalM = init_particles(seed,grid_sz,part_no,par, grid, par_block, n_pr);
  }else{
      par_buffer = (double*) malloc(sizeof(double)*PARBUFFER*5);
      while(1){
          printf("Process: %d   aux_i: %lld\n", p_rank, aux_i);
          MPI_Recv(par_buffer, PARBUFFER*5, MPI_DOUBLE, 0, PARTAG, MPI_COMM_WORLD, &status);
          aux_i = fill_par_buffer(par_buffer, par, aux_i, pr_part_no, grid, grid_sz);
          if(aux_i == pr_part_no)
              break;
      }
  }

  MPI_Barrier (MPI_COMM_WORLD);



  MPI_Barrier (MPI_COMM_WORLD);

  /* ciclo baseado no numero de steps */
  for(i=0; i<steps; i++){
    update_center_local(pr_part_no, grid_sz, grid, par);
    MPI_Barrier (MPI_COMM_WORLD);

    broadcast_mass_centers(grid, p_rank, n_pr, grid_sz); //Mnext = 0 here
    MPI_Barrier (MPI_COMM_WORLD);

    for(j=0; j<pr_part_no; j++){
        move_particle(grid_sz, &par[j], grid, j);
    }
    MPI_Barrier (MPI_COMM_WORLD);

    broadcast_mass(grid, p_rank, n_pr, grid_sz); //center.x && center.y = 0 here
    MPI_Barrier (MPI_COMM_WORLD);
  }

  broadcast_totalM(p_rank, n_pr, &totalM);
  MPI_Barrier (MPI_COMM_WORLD);

  overall_center_local(par, grid, pr_part_no, totalM);
  MPI_Barrier (MPI_COMM_WORLD);

  double x, y;
  broadcast_overall_center(grid, p_rank, n_pr, &x, &y);
  MPI_Barrier (MPI_COMM_WORLD);

  if(p_rank == 0){
    printf("%.2f %.2f\n", par[0].pos.x, par[0].pos.y);
    printf("%.2f %.2f\n", x, y);
  }

  free_all(par, grid, grid_sz); //Frees all memory


  MPI_Finalize();
  return 0;
}
