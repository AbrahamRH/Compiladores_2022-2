#ifndef __ATRIBUTOS_HPP__
#define __ATRIBUTOS_HPP__
#include <string>
using namespace std;

struct expresion{
public:
    int tipo;
    string dir;
};

struct arreglo{
public:
    int tipo;
    int tam;
    string dir;
};

#endif // !__ATRIBUTOS_HPP__