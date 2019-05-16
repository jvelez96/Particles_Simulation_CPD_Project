//physics.c
#include "physics.h"

#define RND0_1 ((double) random() / ((long long)1<<31))

void divide_par(int n_pr, long long part_no, int rem, int *par_block){
  int i;

  for(i=0; i<n_pr; i++){
    par_block[i] = i* floor((double)part_no/(double)n_pr) + min(i, rem);
  }

  return;
}

long long get_par_number(long long part_no, int *par_block, int n_rank, int n_pr){
  long long par_number;

  if(n_rank != n_pr-1)
    par_number = par_block[n_rank+1] - par_block[n_rank];
  else
    par_number = part_no - par_block[n_rank];


  return par_number;
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

//no init particles, arredondar o x e o y, e mete-lo logo na lista da celula certa e ir dando um +=  a uma variavel para termos
//a soma de todas as massas no inicio sem complexidade extra de percorrer todas as listas de novo
//Same para quando as particulas são movimentadas a cada iteração
double init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid, int *par_block, int n_pr){
  long long i;
  int j;
  int x, y;
  double totalM;
  double par_buffer[PARBUFFER*5];
  int pr_counter=1, buf_counter=0;
  int status;

  srandom(seed);
  totalM = 0;

  for(i = 0; i < n_part; i++){
    if(i<par_block[1]){
      par[i].pos.x = RND0_1;
      par[i].pos.y = RND0_1;
      par[i].v.x = (RND0_1 / ncside / 10.0);
      par[i].v.y = (RND0_1 / ncside / 10.0);
      par[i].m = (RND0_1 * ncside / (G * 1e6 * n_part));
      totalM += par[i].m;
    //  printf("P: %lld   %f %f   %f %f   %f\n", i, par[i].pos.x, par[i].pos.y, par[i].v.x, par[i].v.y, par[i].m);

      //Insert in grid after creation
      x = floor(par[i].pos.x * ncside);
      if(x == ncside)
          x = ncside - 1;
      y = floor(par[i].pos.y * ncside);
      if(y == ncside)
          y = ncside - 1;

      grid[x][y].Mnext += par[i].m;
    }else{
      //x
      par_buffer[buf_counter] = RND0_1;
      //y
      par_buffer[buf_counter+1] = RND0_1;
      //vx
      par_buffer[buf_counter+2] = (RND0_1 / ncside / 10.0);
      //vy
      par_buffer[buf_counter+3] = (RND0_1 / ncside / 10.0);
      //m
      par_buffer[buf_counter+4] = (RND0_1 * ncside / (G * 1e6 * n_part));

      totalM += par_buffer[buf_counter+4];

      buf_counter = buf_counter +5;

      //if its not the last process
      if(pr_counter!= n_pr -1){
        //if it is the last particle that the current process treats
        if((i+1) == par_block[pr_counter+1]){
          par_buffer[buf_counter]= -1;
          //send par_buffer
          MPI_Send(par_buffer, PARBUFFER*5, MPI_DOUBLE, pr_counter, PARTAG, MPI_COMM_WORLD);

          //clear par_buffer
          for(j=0; j<buf_counter+1;j++){
            par_buffer[j] = 0.0;
          }

          pr_counter++;
          buf_counter = 0;
        }
      }else if(i==n_part-1){ //if its the last particle send it
        if(buf_counter < PARBUFFER*5)
          par_buffer[buf_counter]= -1;
        //send par_buffer
        MPI_Send(par_buffer, PARBUFFER*5, MPI_DOUBLE, pr_counter, PARTAG, MPI_COMM_WORLD);

        //clear par_buffer
        for(j=0; j<buf_counter+1;j++){
          par_buffer[j] = 0.0;
        }
        buf_counter =0;
      }
      //reached buffer max_length
      if(buf_counter>=PARBUFFER*5){
        //send par_buffer
        MPI_Send(par_buffer, PARBUFFER*5, MPI_DOUBLE, pr_counter, PARTAG, MPI_COMM_WORLD);

        //clear par_buffer
        for(j=0; j<buf_counter;j++){
          par_buffer[j] = 0.0;
        }
        //cada maquina vai ter de adicionar a sua grid as particulas
        buf_counter=0;
      }
    }
  }
  return totalM;
}

long long fill_par_buffer(double *par_buffer, Particle *par, long long aux_i, long long pr_part_no, Grid **grid, long grid_sz){
  long long i;
  long long aux;
  long x,y;

  for(i=aux_i; i<pr_part_no; i++){
    if(par_buffer[i*5] == -1){
      break;
    }else{
      par[i].pos.x = par_buffer[i*5];
      par[i].pos.y = par_buffer[i*5 +1];
      par[i].v.x = par_buffer[i*5 +2];
      par[i].v.y = par_buffer[i*5 +3];
      par[i].m = par_buffer[i*5 +4];

      //Insert in grid after creation
      x = floor(par[i].pos.x * grid_sz);
      if(x == grid_sz)
          x = grid_sz - 1;
      y = floor(par[i].pos.y * grid_sz);
      if(y == grid_sz)
          y = grid_sz - 1;

      grid[x][y].Mnext += par[i].m;
    }
  }
  aux = i;
  return aux;
}

double get_distance(Vector a, Vector b){
  double dx = abs(b.x - a.x);
  double dy = abs(b.y - a.y);

  return sqrt(dx*dx + dy*dy);
}

//Determines force suffered by 1 particle from a single cell
Vector get_force(Particle par, Grid grid, int add_x, int add_y){ //No pointer has been passed, can we manipulate this objects and don't affect main???
  Vector f;
  double ft, d;
  double cosA, senA;

  grid.center.x += add_x;
  grid.center.y += add_y;

  d = get_distance(par.pos, grid.center);
  if(d < EPSLON){
    f.x = 0;
    f.y = 0;
    return f;
  }

  cosA = (grid.center.x - par.pos.x)/d;
  senA = (grid.center.y - par.pos.y)/d;
  ft = (G * par.m * grid.M)/(d*d);
  f.x = cosA * ft;
  f.y = senA * ft;

  return f;
}

Vector sum_forces(Vector *f){
    Vector sum_f;
    int i;

    sum_f.x = 0;
    sum_f.y = 0;

    for(i = 0; i < 8; i++){
        sum_f.x += f[i].x;
        sum_f.y += f[i].y;
    }

    return sum_f;
}

//This function calculates the force that a single particle is subject to, then moves it to next position accordingly
void move_particle(long grid_sz, Particle *par, Grid **grid, long long id){
  int Gx, Gy;
  Vector f[9];
  Vector F;
  Vector a, new_v, new_pos;

  // Position in cell -- No limite tem de andar uma para tras (1.0 * 3 = 3, vector vai de 0 a 2)
  Gx = floor(par->pos.x * grid_sz);
  if(Gx == grid_sz)
      Gx = grid_sz - 1;

  Gy = floor(par->pos.y * grid_sz);
  if(Gy == grid_sz)
      Gy = grid_sz - 1;

  //Determines all forces that the particle is subjected to
  f[0] = get_force(*par, grid[Gx][Gy], 0, 0);

  if(Gy > 0)
    f[1] = get_force(*par, grid[Gx][Gy-1], 0, 0);
  else
    f[1] = get_force(*par, grid[Gx][grid_sz-1], 0, -1);

  if(Gy < grid_sz - 1)
    f[2] = get_force(*par, grid[Gx][Gy+1], 0, 0);
  else
    f[2] = get_force(*par, grid[Gx][0], 0, 1);

  if(Gx > 0){
      f[3] = get_force(*par, grid[Gx-1][Gy], 0, 0);

      if(Gy > 0)
        f[4] = get_force(*par, grid[Gx-1][Gy-1], 0, 0);
      else
        f[4] = get_force(*par, grid[Gx-1][grid_sz-1], 0, -1);

      if(Gy < grid_sz - 1)
        f[5] = get_force(*par, grid[Gx-1][Gy+1], 0, 0);
      else
        f[5] = get_force(*par, grid[Gx-1][0], 0, 1);
  } else{
      f[3] = get_force(*par, grid[grid_sz-1][Gy], -1, 0);

      if(Gy > 0)
        f[4] = get_force(*par, grid[grid_sz-1][Gy-1], -1, 0);
      else
        f[4] = get_force(*par, grid[grid_sz-1][grid_sz-1], -1, -1);

      if(Gy < grid_sz - 1)
        f[5] = get_force(*par, grid[grid_sz-1][Gy+1], -1, 0);
      else
        f[5] = get_force(*par, grid[grid_sz-1][0], -1, 1);
  }

  if(Gx < grid_sz -1){
      f[6] = get_force(*par, grid[Gx+1][Gy], 0, 0);

      if(Gy > 0)
        f[7] = get_force(*par, grid[Gx+1][Gy-1], 0, 0);
      else
        f[7] = get_force(*par, grid[Gx+1][grid_sz-1], 0, -1);

      if(Gy < grid_sz - 1)
        f[8] = get_force(*par, grid[Gx+1][Gy+1], 0, 0);
      else
        f[8] = get_force(*par, grid[Gx+1][0], 0, 1);
  } else{
      f[6] = get_force(*par, grid[0][Gy], 1, 0);

      if(Gy > 0)
        f[7] = get_force(*par, grid[0][Gy-1], 1, 0);
      else
        f[7] = get_force(*par, grid[0][grid_sz-1], 1, -1);

      if(Gy < grid_sz - 1)
        f[8] = get_force(*par, grid[0][Gy+1], 1, 0);
      else
        f[8] = get_force(*par, grid[0][0], 1, 1);
  }

  F = sum_forces(f);

  //Determine acceleration based on force and then new position and velocity
  a.x = F.x/par->m;
  a.y = F.y/par->m;
  new_v.x = par->v.x + a.x;
  new_v.y = par->v.y + a.y;
  new_pos.x = par->pos.x + new_v.x + 0.5*a.x;
  new_pos.y = par->pos.y + new_v.y + 0.5*a.y;

  //Controls passage through walls and multiple laps
  if(new_pos.x > 1)
      new_pos.x = new_pos.x - floor(new_pos.x);
  else if(new_pos.x < 0)
      new_pos.x = 1 - (abs(new_pos.x) - abs(ceil(new_pos.x)));

  if(new_pos.y > 1)
      new_pos.y = new_pos.y - floor(new_pos.y);
  else if(new_pos.y < 0)
      new_pos.y = 1 - (abs(new_pos.y) - abs(ceil(new_pos.y)));



  //Updates particle and grid with new info on this particle
  par->pos = new_pos;
  par->v = new_v;

  Gx = floor(new_pos.x * grid_sz);
  if(Gx == grid_sz)
      Gx = grid_sz - 1;
  Gy = floor(new_pos.y * grid_sz);
  if(Gy == grid_sz)
      Gy = grid_sz - 1;

  grid[Gx][Gy].Mnext += par->m;
}
