#define RND0_1 ((double) random() / ((long long)1<<31))
#define G 6.67408e-11
#define EPSLON 0.0005
#include "physics.h"

//no init particles, arredondar o x e o y, e mete-lo logo na lista da celula certa e ir dando um +=  a uma variavel para termos
//a soma de todas as massas no inicio sem complexidade extra de percorrer todas as listas de novo
//Same para quando as particulas são movimentadas a cada iteração

double init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid){
  long long i;
  int x, y;
  double totalM;

  srandom(seed);
  totalM = 0;

  for(i = 0; i < n_part; i++)
  {
    par[i].setX(RND0_1);
    par[i].setY(RND0_1);
    par[i].setVX(RND0_1 / ncside / 10.0);
    par[i].setVY(RND0_1 / ncside / 10.0);
    par[i].setM(RND0_1 * ncside / (G * 1e6 * n_part)) ;
    totalM += par[i].getM();

    /*std::cout << "X: " << par[i].getX() << std::endl;
    std::cout << "Y: " << par[i].getY() << std::endl;
    std::cout << "VX: " << par[i].getVX() << std::endl;
    std::cout << "VY: " << par[i].getVY() << std::endl;
    std::cout << "M: " << par[i].getM() << std::endl;
    std::cout << "\n";*/

    //Insert in grid after creation
    x = floor(par[i].getX() * ncside);
    y = floor(par[i].getY() * ncside);
    grid[x][y].insert_list(i);
    grid[x][y].add_toM(par[i].getM());
    /*showlist(grid[x][y].par_list);
    printf("x:%lld y:%lld\ntotal M:%f\n",x,y, grid[x][y].getM());*/
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

  grid.setX(grid.getX() + add_x);
  grid.setY(grid.getY() + add_y);

  d = get_distance(par.getPos(), grid.getCenter());
  if(d < EPSLON){
    f.x = 0;
    f.y = 0;
    return f;
  }

  cosA = (grid.getX() - par.getX())/d;
  senA = (grid.getY() - par.getY())/d;
  ft = G/(d*d) * par.getM() * grid.getM();
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
  Gx = floor(par->getX() * grid_sz);
  if(Gx == grid_sz)
      Gx = grid_sz - 1;

  Gy = floor(par->getY() * grid_sz);
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
  a.x = F.x/par->getM();
  a.y = F.y/par->getM();
  new_v.x = par->getVX() + a.x;
  new_v.y = par->getVY() + a.y;
  new_pos.x = par->getX() + new_v.x + 0.5*a.x;
  new_pos.y = par->getY() + new_v.y + 0.5*a.y;

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
  par->setPos(new_pos);
  par->setV(new_v);
  Gx = floor(par->getX() * grid_sz);
  Gy = floor(par->getY() * grid_sz);
  grid[Gx][Gy].insert_list(id);
  grid[Gx][Gy].add_toMnext(par->getM());

  printf("%lld \n", id);
}




void showlist(std::list <int> g)
{
    std::list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        std::cout << '\t' << *it;
    std::cout << '\n';
}
