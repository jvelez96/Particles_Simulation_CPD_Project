// grid.h
#include "particle.h"

class Grid {
  public:
    Grid();
    void setX(double x_new);
    double getX();
    void setY(double x_new);
    double getY();
    void setVX(double x_new);
    double getVX();
    void setVY(double x_new);
    double getVY();
    void setM(double x_new);
    double getM();
  private:
    double x;
    double y;
    double vx;
    double vy;
    double m;
};
