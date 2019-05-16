#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#define BILLION 1E9
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

void divide_par(int n_pr, int part_no, int rem, int *par_block){
  int i;

  for(i=0; i<n_pr; i++){
    par_block[i] = i* floor((double)part_no/(double)n_pr) + min(i, rem);
  }

  return;
}

int task_owner(int part_no, int n_pr, int rem, int par){
  int i;
  int owner;
  int nmax1, nmax2;
  int n;
  double div;
  div = (double)part_no/(double)n_pr;
  n = ceil(div);
  nmax1 = floor((double)par/(double)n);
  nmax2 = floor((par-rem)/floor((double)part_no/(double)n_pr));

  owner = max(nmax1, nmax2);

  return owner;
}

int main (int argc, char* argv[]) {
  int p_rank, n_pr, part_no;
  int *par_block;
  int rem;
  int a, b;
  int i;

  n_pr = 4;
  part_no = 14;

  par_block = malloc(sizeof(int)* n_pr);
  rem = part_no % n_pr;

  printf("remainder = %d\n", rem);
  divide_par(n_pr, part_no, rem, par_block);

  for(i=0;i<n_pr;i++){
    printf("%d\n", par_block[i]);
  }

  a = task_owner(part_no, n_pr, rem, 7);
  b = task_owner(part_no, n_pr, rem, 8);

  printf("7 in machine %d\n8 in machine %d\n", a, b);

  return 0;
}
