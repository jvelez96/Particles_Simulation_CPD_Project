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


class Particle {
  public:
    Particle();
    void setAll(long double x_new, long double y_new, long double vx_new, long double vy_new, long double m_new);

    void setX(long double x_new);
    long double getX();
    void setY(long double x_new);
    long double getY();
    void setVX(long double x_new);
    long double getVX();
    void setVY(long double x_new);
    long double getVY();
    void setM(long double x_new);
    long double getM();

  private:
    long double x;
    long double y;
    long double vx;
    long double vy;
    long double m;
};
