//grid.c
#include "grid.h"

Grid::Grid() {
   std::cout << "Grid created" << std::endl;
}

void Grid::insert_list(int new_par){
  par_list.push_front(new_par);
}

void Grid::clear_particles(){ //Erases all paricles in a cell to start new movement
  M = 0;
  par_list.clear();
}

void Grid::setX (long double x_new) {
    center.x = x_new;
}

long double Grid::getX () {
    return center.x;
}

void Grid::add_toX(long double x_new){
    center.x += x_new;
}

void Grid::setY (long double y_new) {
    center.y = y_new;
}

long double Grid::getY () {
    return center.y;
}

void Grid::add_toY (long double y_new) {
    center.y += y_new;
}

void Grid::setM(long double m_new){
    M = m_new;
}

long double Grid::getM () {
    return M;
}

void Grid::add_toM(long double m_new){
    M += m_new;
}

void Grid::setCenter(Vector center_new){
    center.x = center_new.x;
    center.y = center_new.y;
}

Vector Grid::getCenter() {
    return center;
}


//Aqui vai-se calcular o centro de massa (x, y) de uma celula com a expressao 1/M* E(mi * (x,y))
//A lista já se encontra completa e a massa total calculada
void Grid::update_center(Particle *par){
  std::list <int> :: iterator it;
  long double new_x, new_y;
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
