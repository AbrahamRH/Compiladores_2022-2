#ifndef __GENERATOR_HPP_
#define __GENERATOR_HPP_
#include <string>
#include <vector>
#include <fstream>
#include "Cuadrupla.hpp"
using namespace std;
class Generator
{
  private: 
    std::ofstream file;
  public:
    Generator() = default;
    Generator(string file);
    ~Generator()=default;
    void translate(std::vector<Cuadrupla> code);
    void translate(Cuadrupla c, int tipo);

};
#endif