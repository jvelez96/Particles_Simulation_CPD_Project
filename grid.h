// grid.h
#include "particle.h"

class Grid {
  public:
    Grid();
    void setX(double x_new);
    double getX();
    void setY(double x_new);
    double getY();
    void calculateM(double x_new);
    double getM();

    //definir o remover e adicionar de uma lista
  private:
    double x;
    double y;
    double vx;
    double vy;
    double M;
    Particle *par;
};

void init_grid(int grid_sz,Grid **grid);
