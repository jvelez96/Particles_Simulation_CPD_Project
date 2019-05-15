#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#define BILLION 1E9
#define min(a, b) (((a) < (b)) ? (a) : (b))

void divide_cells(int n_pr, int grid_sz, int rem, int *cell_block){
  int i;

  for(i=0; i<n_pr; i++){
    cell_block[i] = i* floor(grid_sz/n_pr) + min(i, rem);
  }

  return;
}

void task_owner(int )

int main (int argc, char* argv[]) {
  int p_rank, n_pr, grid_sz;
  int *cell_block;
  int rem;
  int i;

  n_pr = 4;
  grid_sz = 14;

  cell_block = malloc(sizeof(int)* n_pr);
  rem = grid_sz % n_pr;

  divide_cells(n_pr, grid_sz, rem, cell_block);

  for(i=0;i<n_pr;i++){
    printf("%d\n", cell_block[i]);
  }

  return 0;
}
