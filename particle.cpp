// particle.cpp
#include "particle.h"

Particle::Particle() {
   std::cout << "Particle created" << std::endl;
}


void Particle::setAll(long double x_new, long double y_new, long double vx_new, long double vy_new, long double m_new) {
    x = x_new;
    y = y_new;
    vx = vx_new;
    vy = vy_new;
    m = m_new;
}

void Particle::setX (long double x_new) {
    x = x_new;
}

long double Particle::getX () {
    return x;
}

void Particle::setY (long double y_new) {
    y = y_new;
}

long double Particle::getY () {
    return y;
}

void Particle::setVX (long double vx_new) {
    vx = vx_new;
}

long double Particle::getVX () {
    return vx;
}

void Particle::setVY (long double vy_new) {
    vy = vy_new;
}

long double Particle::getVY () {
    return vy;
}

void Particle::setM (long double m_new) {
    m = m_new;
}

long double Particle::getM () {
    return m;
}
