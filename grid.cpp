//grid.c
#include "grid.h"

Grid::Grid() {
   /*std::cout << "Grid created" << std::endl;*/
}

void Grid::insert_list(int new_par){
  par_list.push_front(new_par);
}

void Grid::clear_particles(){ //Erases all paricles in a cell to start new movement
  Mnext = 0;
  par_list.clear();
}

void Grid::swap_Ms(){
  M = Mnext;
}

void Grid::setX (double x_new) {
    center.x = x_new;
}

double Grid::getX () {
    return center.x;
}

void Grid::add_toX(double x_new){
    center.x += x_new;
}

void Grid::setY (double y_new) {
    center.y = y_new;
}

double Grid::getY () {
    return center.y;
}

void Grid::add_toY (double y_new) {
    center.y += y_new;
}

void Grid::setM(double m_new){
    M = m_new;
}

double Grid::getM () {
    return M;
}

void Grid::add_toM(double m_new){
    M += m_new;
}

void Grid::setMnext(double m_new){
    Mnext = m_new;
}

double Grid::getMnext () {
    return Mnext;
}

void Grid::add_toMnext(double m_new){
    Mnext += m_new;
}

void Grid::setCenter(Vector center_new){
    center.x = center_new.x;
    center.y = center_new.y;
}

Vector Grid::getCenter() {
    return center;
}


//A lista já se encontra completa e a massa total calculada
void Grid::update_center(Particle *par){
  std::list <int> :: iterator it;
  double new_x, new_y;
  center.x=0;
  center.y=0;
  // Conforme
  for(it = par_list.begin(); it != par_list.end(); ++it){
    new_x = (par[*it].getX() * par[*it].getM())/M;
    center.x += new_x;
    new_y = (par[*it].getY() * par[*it].getM())/M;
    center.y += new_y;
  }
}


// --------------------  General Functions ------------------------------

void init_grid (int size, Grid **grid){
  int i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].setX(0);
      grid[i][j].setY(0);
      grid[i][j].setM(0);
    }
  }
}

void clear_grid (int size, Grid **grid){
  int i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].clear_particles();
    }
  }
}

void swap_grid_Ms (int size, Grid **grid){
  int i, j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].swap_Ms();
    }
  }
}

/* Função para fazer o update geral de todos os centros de massa com base nas particulas que tem no momento */
void update_center_all (int size, Grid **grid, Particle *par){
  int i, j;

  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      grid[i][j].update_center(par);
      std::cout << "Center of Mass\nX:" << grid[i][j].getX() << std::endl;
      std::cout << "Y: " << grid[i][j].getY() << std::endl;
    }
  }
}

/* Function to calculate overall center of mass and print it*/
void overall_center(Particle *par, long long part_no, double totalM){
  long long i;
  double x=0, y=0;
  for(i=0; i<part_no; i++){
    x += (par[i].getX() * par[i].getM())/totalM;
    y += (par[i].getY() * par[i].getM())/totalM;
  }
  std::cout << "Final Center of mass\nX: " << x << " Y: " << y << std::endl;

}
