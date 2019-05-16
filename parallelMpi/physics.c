//physics.c
#include "physics.h"

#define RND0_1 ((double) random() / ((long long)1<<31))
#define G 6.67408e-11
#define EPSLON 0.0005

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

//no init particles, arredondar o x e o y, e mete-lo logo na lista da celula certa e ir dando um +=  a uma variavel para termos
//a soma de todas as massas no inicio sem complexidade extra de percorrer todas as listas de novo
//Same para quando as particulas são movimentadas a cada iteração
double init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid){
  long long i;
  int x, y;
  double totalM;

  srandom(seed);
  totalM = 0;

  for(i = 0; i < n_part; i++){
    par[i].pos.x = RND0_1;
    par[i].pos.y = RND0_1;
    par[i].v.x = (RND0_1 / ncside / 10.0);
    par[i].v.y = (RND0_1 / ncside / 10.0);
    par[i].m = (RND0_1 * ncside / (G * 1e6 * n_part));
    totalM += par[i].m;

    //Insert in grid after creation
    x = floor(par[i].pos.x * ncside);
    if(x == ncside)
        x = ncside - 1;
    y = floor(par[i].pos.y * ncside);
    if(y == ncside)
        y = ncside - 1;

    grid[x][y].M += par[i].m;

  }
  return totalM;
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
