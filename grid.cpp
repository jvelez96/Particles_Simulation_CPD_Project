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

void Grid::setY (double y_new) {
    y = y_new;
}

double Grid::getY () {
    return y;
}


//Aqui vai-se calcular o centro de massa (x, y) de uma celula com a expressao 1/M* E(mi * (x,y))


void Grid::setM (double m_new) {
    M = m_new;
}

double Grid::getM () {
    return M;
}
