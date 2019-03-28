// particle.cpp
#include "particle.h"

Particle::Particle() {
   std::cout << "Particle created" << std::endl;
}


void Particle::setAll(double x_new, double y_new, double vx_new, double vy_new, double m_new) {
    x = x_new;
    y = y_new;
    vx = vx_new;
    vy = vy_new;
    m = m_new;
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
