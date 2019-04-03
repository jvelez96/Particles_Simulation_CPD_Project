//grid.c
#include "grid.h"

Grid **init_grid(int size){
    int i, j;

    Grid **grid = NULL;

    grid = (Grid**) malloc(sizeof(Grid*) * size);

    for(i=0;i<size;i++){
        grid[i] = (Grid*) malloc(sizeof(Grid) * size);
        for(j=0;j<size;j++){
            grid[i][j].center.x = 0;
            grid[i][j].center.y = 0;
            grid[i][j].M = 0;
            grid[i][j].Mnext = 0;
            grid[i][j].par_list = initLinkedList();
        }
    }

    return grid;
}

void clear_grid (int size, Grid **grid){
  int i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].Mnext = 0;
      freeLinkedList(grid[i][j].par_list);
      grid[i][j].par_list = initLinkedList();
    }
  }
}

void swap_grid_Ms (int size, Grid **grid){
  int i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].M = grid[i][j].Mnext;
    }
  }
}

//A lista já se encontra completa e a massa total calculada
void update_center_one(Particle *par, Grid *grid){
  long long i;
  double new_x, new_y;
  double x = 0, y = 0; //Criamos variaveis auxiliares para nao ir à memoria alterar o valor cada vez que se incrementa, péssima performance
  LinkedList *curr = grid->par_list;

  while(curr != NULL){
    i = getItemLinkedList(curr);

    new_x = (par[i].pos.x * par[i].m)/grid->M;
    x += new_x;
    new_y = (par[i].pos.y * par[i].m)/grid->M;
    y += new_y;

    curr = getNextNodeLinkedList(curr);
  }

  grid->center.x = x;
  grid->center.y = y;
}

/* Função para fazer o update geral de todos os centros de massa com base nas particulas que tem no momento */
void update_center_all (int size, Grid **grid, Particle *par){
  int i, j;

  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      update_center_one(par, &grid[i][j]);

      printf("Center of Mass\nX: %f\n", grid[i][j].center.x);
      printf("Center of Mass\nY: %f\n", grid[i][j].center.y);
    }
  }
}

/* Function to calculate overall center of mass and print it*/
void overall_center(Particle *par, long long part_no, double totalM){
  long long i;
  double x=0, y=0;
  for(i=0; i<part_no; i++){
    x += (par[i].pos.x * par[i].m)/totalM;
    y += (par[i].pos.y * par[i].m)/totalM;
  }
  printf("Final Center of mass\nX: %f Y: %f\n", x, y);
}
