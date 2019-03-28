// grid.h
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

  private:
    double x;
    double y;
    double M;

};

void init_grid(int grid_sz,Grid **grid);
void showlist(std::list <int> g);
