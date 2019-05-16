//grid.c
#include "grid.h"

int cell_id(int x, int y, int grid_sz){
  int cell;

  cell = (y*grid_sz + x);

  return cell;
}

Grid **init_grid(long size){
    long i, j;

    Grid **grid = NULL;

    grid = (Grid**) malloc(sizeof(Grid*) * size);

    for(i=0;i<size;i++){
        grid[i] = (Grid*) malloc(sizeof(Grid) * size);
        for(j=0;j<size;j++){
            grid[i][j].center.x = 0;
            grid[i][j].center.y = 0;
            grid[i][j].M = 0;
            grid[i][j].Mnext = 0;
        }
    }

    return grid;
}

void clear_grid (long size, Grid **grid){
  long i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].Mnext = 0;
    }
  }
}

void swap_grid_Ms (long size, Grid **grid){
  long i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].M = grid[i][j].Mnext;
      grid[i][j].center.x = 0; //Clears mass centers for next iteration
      grid[i][j].center.y = 0;
    }
  }
}

/* Função para fazer o update geral de todos os centros de massa*/
void update_center_all (long long part_no, long size, Grid **grid, Particle *par){
  long long i;
  int Gx, Gy;
  double new_x, new_y;

  for(i=0;i<part_no;i++){
      Gx = floor(par[i].pos.x * size);
      if(Gx == size)
          Gx = size - 1;
      Gy = floor(par[i].pos.y * size);
      if(Gy == size)
          Gy = size - 1;


      new_x = (par[i].pos.x * par[i].m)/grid[Gx][Gy].M;
      grid[Gx][Gy].center.x += new_x;
      new_y = (par[i].pos.y * par[i].m)/grid[Gx][Gy].M;
      grid[Gx][Gy].center.y += new_y;
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

  //printf("Final Center of mass\nX: %.2f Y: %.2f\n", x, y);
  printf("%.2f %.2f\n", x, y);
}

void free_all(Particle *par, Grid  **grid, long grid_sz){
  long i, j;

  free(par);
  for(i = 0; i < grid_sz; i++)
    free(grid[i]);
  free(grid);
}
