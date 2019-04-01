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
    long double x;
    long double y;
};

class Particle {
  public:
    Particle();
    void setAll(long double x_new, long double y_new, long double vx_new, long double vy_new, long double m_new);

    void setX(long double x_new);
    long double getX();
    void setY(long double y_new);
    long double getY();
    void setVX(long double vx_new);
    long double getVX();
    void setVY(long double vy_new);
    long double getVY();
    void setM(long double m_new);
    long double getM();

    void setPos(Vector pos_new);
    Vector getPos();
    void setV(Vector v_new);
    Vector getV();

  private:
    Vector pos; //Position in x and y
    Vector v; //Velocity in x and y
    long double m;
};
