// main.cpp
#include "particle.h"

int main () {
  int i;
  int a;

  std::cout << "Input: " << std::endl;
  std::cin >> a;

  Particle par[a];

  for(i=0; i<a; i++){
    par[i].setAll(0.23, 0.45, 0.67, 0.78, 23);
    std::cout << "X: " << par[i].getX() << std::endl;
    std::cout << "Y: " << par[i].getY() << std::endl;
    std::cout << "VX: " << par[i].getVX() << std::endl;
    std::cout << "VY: " << par[i].getVY() << std::endl;
    std::cout << "M: " << par[i].getM() << std::endl;
    std::cout << "\n";
  }



  return 0;
}
