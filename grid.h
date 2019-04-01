// grid.h
#include "particle.h"

class Grid {
  public:
    std::list<int> par_list;

    Grid();
    void insert_list(int new_par);
    void clear_particles();

    void setX(long double x_new);
    long double getX();
    void add_toX(long double y_new);
    void setY(long double x_new);
    long double getY();
    void add_toY(long double y_new);
    void setM(long double M_new);
    long double getM();
    void add_toM(long double m_new);

    void setCenter(Vector center_new);
    Vector getCenter();

    void update_center(Particle *par);

  private:
    Vector center; //Coordinates of center of mass
    long double M; //Total mass

};

void init_grid(int size, Grid **grid);
void clear_grid(int size, Grid **grid);
void update_center_all(int size, Grid **grid, Particle *par);
