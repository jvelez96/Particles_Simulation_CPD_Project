// particle.cpp
#include "particle.h"

Particle::Particle() {
   /*std::cout << "Particle created" << std::endl;*/
}


void Particle::setAll(double x_new, double y_new, double vx_new, double vy_new, double m_new) {
    pos.x = x_new;
    pos.y = y_new;
    v.x = vx_new;
    v.y = vy_new;
    m = m_new;
}

void Particle::setX (double x_new) {
    pos.x = x_new;
}

double Particle::getX () {
    return pos.x;
}

void Particle::setY (double y_new) {
    pos.y = y_new;
}

double Particle::getY () {
    return pos.y;
}

void Particle::setVX (double vx_new) {
    v.x = vx_new;
}

double Particle::getVX () {
    return v.x;
}

void Particle::setVY (double vy_new) {
    v.y = vy_new;
}

double Particle::getVY () {
    return v.y;
}

void Particle::setM (double m_new) {
    m = m_new;
}

double Particle::getM () {
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
