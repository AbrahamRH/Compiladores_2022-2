#ifndef __GENERATOR_HPP_
#define __GENERATOR_HPP_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Cuadrupla.hpp"
#include "TS.hpp"
#include "TT.hpp"
using namespace std;
class Generator
{
  private: 
    string filename;
    std::ofstream file;
    void generateFile(string ext);
  public:
    Generator() = default;
    ~Generator()=default;
    void setFilename(string filename);
    void translate(std::vector<Cuadrupla> code, std::map<std::string, symbols> TablaS, std::map<int,types> TablaT, std::map<string, string> constFloat);
    void translate(Cuadrupla c, int tipo);
    void intermedio(vector<Cuadrupla> code, std::map<std::string, symbols> TablaS, std::map<int,types> TablaT, std::map<string, string> constFloat);

};
#endif
