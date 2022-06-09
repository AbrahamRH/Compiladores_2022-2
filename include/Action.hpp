#ifndef __ACTION_HPP__
#define __ACTION_HPP__
#include <string>
#include <iostream>
using namespace std;
#include <vector>
#include "Atributos.hpp"
#include "Cuadrupla.hpp"
#include "TS.hpp"
#include "TT.hpp"


class Action
{
private:
    /* data */
    int dir=0;
    void error(string msg);
    int numEtq=0;
    int numTemp=0;
    int numConst = 0;
    vector<Cuadrupla> codInt;
    map<string, string> constFloat; //{id, val}

public:
    TT TablaT;
    TS TablaS;
    Action(/* args */);
    ~Action();
    TT getTT();
    TS getTablaSimbolos();
    int validarDimensionArreglo(int tipo, string val, int base);
    void agregarSimbolo(string id, int tipo, string categoria);
    int agregarTipo(string valor, int basetype);
    void existe(string id);
    string nuevaEtiqueta(); // str - convierte el objeto en un string
    string nuevaTemporal(); // inciar un valor iniciar 0 o 1 
    void genCod(string op, string op1, string op2, string res);
    bool equivalentes(int tipo1, int tipo2);
    void asignacion(string id, expresion e);
    void asignacion(string id, string des, expresion e);
    string reducir(string dir, int tipoOrg, int tipoDest);
    string ampliar(string dir, int tipoOrg, int tipoDest);
    int maximo(int tipo1, int tipo2);
    int minimo(int tipo1, int tipo2);
    void validar_array(int tipo);
    void validar_indice(int tipo);
    void suma(expresion e1,expresion e2);
    vector<Cuadrupla> getCodInt();
    expresion agregarConstFloat(expresion F);
    map<string, string> getConstF();
};




#endif // !__ACTION_HPP__
