// particle.h
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<list>
#include<iterator>

struct Vector {
    double x;
    double y;
};

class Particle {
  public:
    Particle();
    void setAll(double x_new, double y_new, double vx_new, double vy_new, double m_new);

    void setX(double x_new);
    double getX();
    void setY(double y_new);
    double getY();
    void setVX(double vx_new);
    double getVX();
    void setVY(double vy_new);
    double getVY();
    void setM(double m_new);
    double getM();

    void setPos(Vector pos_new);
    Vector getPos();
    void setV(Vector v_new);
    Vector getV();

  private:
    Vector pos; //Position in x and y
    Vector v; //Velocity in x and y
    double m;
};
