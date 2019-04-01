// particle.cpp
#include "particle.h"

Particle::Particle() {
   std::cout << "Particle created" << std::endl;
}


void Particle::setAll(long double x_new, long double y_new, long double vx_new, long double vy_new, long double m_new) {
    pos.x = x_new;
    pos.y = y_new;
    v.x = vx_new;
    v.y = vy_new;
    m = m_new;
}

void Particle::setX (long double x_new) {
    pos.x = x_new;
}

long double Particle::getX () {
    return pos.x;
}

void Particle::setY (long double y_new) {
    pos.y = y_new;
}

long double Particle::getY () {
    return pos.y;
}

void Particle::setVX (long double vx_new) {
    v.x = vx_new;
}

long double Particle::getVX () {
    return v.x;
}

void Particle::setVY (long double vy_new) {
    v.y = vy_new;
}

long double Particle::getVY () {
    return v.y;
}

void Particle::setM (long double m_new) {
    m = m_new;
}

long double Particle::getM () {
    return m;
}


void Particle::setPos(Vector pos_new){
    pos.x = pos_new.x;
    pos.y = pos_new.y;
}

Vector Particle::getPos() {
    return pos;
}

void Particle::setV(Vector v_new){
    v.x = v_new.x;
    v.y = v_new.y;
}

Vector Particle::getV() {
    return v;
}
