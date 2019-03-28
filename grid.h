// grid.h
#include "particle.h"

class Grid {
  public:
    Grid();
    void setX(double x_new);
    double getX();
    void add_toX(double y_new);
    void setY(double x_new);
    double getY();
    void add_toY(double y_new);
    void setM(double M_new);
    double getM();
    void insert_list(int new_par);
    std::list<int> par_list;
    void add_toM(double m_new);
    void update_center(Particle *par);

  private:
    double x;
    double y;
    double M;

};

void init_grid(int grid_sz,Grid **grid);
void showlist(std::list <int> g);
void init_particles(long seed, long ncside, long long n_part, Particle *par, Grid **grid);
void update_center_all(int size,Grid **grid, Particle *par);
