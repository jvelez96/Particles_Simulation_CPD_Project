//grid.c
#include "grid.h"

Grid::Grid() {
   std::cout << "Grid created" << std::endl;
}

void Particle::setX (double x_new) {
    x = x_new;
}

double Particle::getX () {
    return x;
}

void Particle::setY (double y_new) {
    y = y_new;
}

double Particle::getY () {
    return y;
}

void Particle::setVX (double vx_new) {
    vx = vx_new;
}

double Particle::getVX () {
    return vx;
}

void Particle::setVY (double vy_new) {
    vy = vy_new;
}

double Particle::getVY () {
    return vy;
}

void Particle::setM (double m_new) {
    m = m_new;
}

double Particle::getM () {
    return m;
}
