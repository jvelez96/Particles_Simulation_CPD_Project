// grid.h
#include "particle.h"

class Grid {
  public:
    std::list<int> par_list;

    Grid();
    void insert_list(int new_par);
    void clear_particles();
    void swap_Ms();

    void setX(double x_new);
    double getX();
    void add_toX(double y_new);
    void setY(double x_new);
    double getY();
    void add_toY(double y_new);
    void setM(double M_new);
    double getM();
    void add_toM(double m_new);
    void setMnext(double Mnext_new);
    double getMnext();
    void add_toMnext(double mnext_new);

    void setCenter(Vector center_new);
    Vector getCenter();

    void update_center(Particle *par);

  private:
    Vector center; //Coordinates of center of mass
    double M; //Total mass
    double Mnext; //Total mass

};

void init_grid(int size, Grid **grid);
void clear_grid(int size, Grid **grid);
void swap_grid_Ms (int size, Grid **grid);
void update_center_all(int size, Grid **grid, Particle *par);
