#define RND0_1 ((double) random() / ((long long)1<<31))
#define G 6.67408e-11
#define EPSLON 0.01
#include "particle.h"

void showlist(std::list <int> g)
{
    std::list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        std::cout << '\t' << *it;
    std::cout << '\n';
}

//no init particles, arredondar o x e o y, e mete-lo logo na lista da celula certa e ir dando um +=  a uma variavel para termos
//a soma de todas as massas no inicio sem complexidade extra de percorrer todas as listas de novo

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
    std::cout << "X: " << par[i].getX() << std::endl;
    std::cout << "Y: " << par[i].getY() << std::endl;
    std::cout << "VX: " << par[i].getVX() << std::endl;
    std::cout << "VY: " << par[i].getVY() << std::endl;
    std::cout << "M: " << par[i].getM() << std::endl;
    std::cout << "\n";
    x = floor(par[i].getX() * ncside);
    y = floor(par[i].getY() * ncside);
    grid[x][y].insert_list(i);
    grid[x][y].add_toM(par[i].getM());
    showlist(grid[x][y].par_list);
    printf("x:%lld y:%lld\ntotal M:%f\n",x,y, grid[x][y].getM());
  }
}

//desnecessaria
void init_grid(int size, Grid **grid){
  long long i, j;
  for(i=0; i< size;i++){
    for(j=0;j<size;j++){
      grid[i][j].setX(0);
      grid[i][j].setY(0);
      /*
      std::cout << "X: " << grid[i][j].getX() << std::endl;
      std::cout << "Y: " << grid[i][j].getY() << std::endl;
      */
    }
  }
}

//fazer a funcao para atualizar o centro de massa  de todas as celulas
