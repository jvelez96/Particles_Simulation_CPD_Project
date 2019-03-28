//grid.c
#include "grid.h"

Grid::Grid() {
   std::cout << "Grid created" << std::endl;
}

void Grid::setX (double x_new) {
    x = x_new;
}

double Grid::getX () {
    return x;
}
void Grid::add_toX(double x_new){
  x += x_new;
}

void Grid::setY (double y_new) {
    y = y_new;
}

double Grid::getY () {
    return y;
}

void Grid::add_toY (double y_new) {
    y += y_new;
}


void Grid::insert_list(int new_par){
  par_list.push_front(new_par);
}

//fazer funçao para limpar a lista

void Grid::setM(double m_new){
  M = m_new;
}

void Grid::add_toM(double m_new){
  M += m_new;
}

//Aqui vai-se calcular o centro de massa (x, y) de uma celula com a expressao 1/M* E(mi * (x,y))

double Grid::getM () {
    return M;
}

void Grid::update_center(Particle *par){
  std::list <int> :: iterator it;
  double new_x, new_y;
  x=0;
  y=0;
  for(it = par_list.begin(); it != par_list.end(); ++it){
    new_x = (par[*it].getX() * par[*it].getM())/M;
    x += new_x;
    new_y = (par[*it].getY() * par[*it].getM())/M;
    y += new_y;
  }
}
/* Função para fazer o update geral de todos os centros de massa com base nas particulas que tem no momento */
void update_center_all (int size,Grid **grid, Particle *par){

  int i, j;
  double new_x, new_y;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      /*
      grid[i][j].setX(0);
      grid[i][j].setY(0);

      std::list <int> :: iterator it;
      for(it = grid[i][j].par_list.begin(); it != grid[i][j].par_list.end(); ++it){
        new_x = (par[*it].getX() * par[*it].getM())/grid[i][j].getM();
        grid[i][j].add_toX(new_x);
        new_y = (par[*it].getY() * par[*it].getM())/grid[i][j].getM();
        grid[i][j].add_toY(new_y);
      }*/
      grid[i][j].update_center(par);
      std::cout << "Center of Mass\nX:" << grid[i][j].getX() << std::endl;
      std::cout << "Y: " << grid[i][j].getY() << std::endl;
      //Percorrer a lista desta celula e
      /*
      std::cout << "X: " << grid[i][j].getX() << std::endl;
      std::cout << "Y: " << grid[i][j].getY() << std::endl;
      */

    }
  }
}
