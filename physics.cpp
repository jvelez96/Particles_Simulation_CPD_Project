#define RND0_1 ((double) random() / ((long long)1<<31))
#define G 6.67408e-11
#define EPSLON 0.01
#include "physics.h"

long double get_distance(long double x1, long double y1, long double x2, long double y2){
  long double dx = abs(x2 - x1);
  long double dy = abs(y2 - y1);

  return sqrt(dx*dx + dy*dy);
}

//Determines force suffered by 1 particle from a single cell
long double get_force(Particle par, Grid grid){
  long double f, fx, fy, d, az, ay;
  long double cosA, senA;

  d = get_distance(par.getX(), par.getY(), grid.getX(), grid.getY());
  cosA = (grid.getX() - par.getX())/d;
  senA = (grid.getY() - par.getY())/d;
  f = G * (par.getM() * grid.getM())/(d*d);
  fx = cosA * f;
  fy = senA * f;
  ax = fx/par.getM();
  ay = fy/par.getM();


}


void showlist(std::list <int> g)
{
    std::list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        std::cout << '\t' << *it;
    std::cout << '\n';
}

//no init particles, arredondar o x e o y, e mete-lo logo na lista da celula certa e ir dando um +=  a uma variavel para termos
//a soma de todas as massas no inicio sem complexidade extra de percorrer todas as listas de novo
//Same para quando as particulas são movimentadas a cada iteração

void init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid){
  long long i, x, y;

  srandom(seed);

  for(i = 0; i < n_part; i++)
  {
    par[i].setX(RND0_1);
    par[i].setY(RND0_1);
    par[i].setVX(RND0_1 / ncside / 10.0);
    par[i].setVY(RND0_1 / ncside / 10.0);
    par[i].setM( RND0_1 * ncside / (G * 1e6 * n_part)) ;

    /*std::cout << "X: " << par[i].getX() << std::endl;
    std::cout << "Y: " << par[i].getY() << std::endl;
    std::cout << "VX: " << par[i].getVX() << std::endl;
    std::cout << "VY: " << par[i].getVY() << std::endl;
    std::cout << "M: " << par[i].getM() << std::endl;
    std::cout << "\n";*/
    x = floor(par[i].getX() * ncside);
    y = floor(par[i].getY() * ncside);
    grid[x][y].insert_list(i);
    grid[x][y].add_toM(par[i].getM());
    showlist(grid[x][y].par_list);
    printf("x:%lld y:%lld\ntotal M:%Lf\n",x,y, grid[x][y].getM());
  }
}

//This function calculates the force that a single particle is subject to, then moves it to next position accordingly
void move_particle(long grid_sz, Particle par, Grid **grid){
  int Gxi, Gyi, Gx, Gy;
  long double f1=0,f2=0,f3=0,f4=0,f5=0,f6=0,f7=0,f8=0,f9=0;
  long double f1x=0,f2x=0,f3x=0,f4x=0,f5x=0,f6x=0,f7x=0,f8x=0,f9x=0;
  long double f1y=0,f2y=0,f3y=0,f4y=0,f5y=0,f6y=0,f7y=0,f8y=0,f9y=0;
  long double d1,d2,d3,d4,d5,d6,d7,d8,d9;
  long double a1,a2,a3,a4,a5,a6,a7,a8,a9;

  //F1 - force on it's own cell
  Gxi = Gx = floor(par.getX() * grid_sz);
  Gyi = Gy = floor(par.getY() * grid_sz);
  d1 = get_distance(par.getX(), par.getY(), grid[Gx][Gy].getX(), grid[Gx][Gy].getY());
  f1 = G * (par.getM() * grid[Gx][Gy].getM())/(d1*d1);
  a1 = f1/par.getM();




  if(grid_sz > 2){

  }

}
