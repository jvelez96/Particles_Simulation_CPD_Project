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

class Particle {
  public:
    Particle();
    void setAll(double x_new, double y_new, double vx_new, double vy_new, double m_new);

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

void init_particles(long seed, long ncside, long long n_part, Particle *par);
