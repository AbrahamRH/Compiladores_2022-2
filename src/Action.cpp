#include "../include/Action.hpp"

Action::Action(/* args */)
{
    numEtq = 0;
}

Action::~Action()
{
}


int Action::validarDimensionArreglo(int tipo, string val, int base)
{
    if(tipo == 0){
        return TablaT.agregar(val, base);
    }else{
        error("La expresión no es del  tipo int");
    return 0;
    }
}


void Action::agregarSimbolo(string id, int tipo, string categoria)
{
    if(!TablaS.existe(id)){
        TablaS.agregar(id, dir, tipo, categoria);
        dir += TablaT.getSize(tipo);
    }else{
        error("El id " + id + " ya fue definido");
    }
}

int Action::agregarTipo(string valor, int basetype)
{
    return TablaT.agregar(valor, basetype);
}

void Action::error(string msg){
    cout<<"ERROR SEMÁNTICO: "<<msg<<endl;
    exit(EXIT_FAILURE);
}

void Action::existe(string id)
{
    if(!TablaS.existe(id)){
        error("El id "+id+" no se declaro");
    }
}


void Action::genCod(string op, string op1, string op2, string res)
{
    codInt.push_back({op, op1, op2, res});
}

void Action::asignacion(string id, expresion e)
{
    string temp;
    int tipo = TablaS.getType(id);
    if(equivalentes(tipo, e.tipo)){
        temp = reducir(e.dir, e.tipo, tipo);
        genCod("", " = ", e.dir, id);
    }
}


void Action::asignacion(string id, string des, expresion e)
{
    string temp;
    int tipo = TablaS.getType(id);
    if(equivalentes(tipo, e.tipo)){
        temp = reducir(e.dir, e.tipo, tipo);
        string dir = id+"["+des+"]";
        genCod("=", e.dir, "", dir);
    }
}

void Action::suma(expresion e1, expresion e2)
{
    if(equivalentes(e1.tipo, e2.tipo)){
        //TODO implementar
    }
}

void Action::validar_array(int tipo)
{
    if(TablaT.getName(tipo)!="array"){
        error("El id no es un arreglo");
    }
}

void Action::validar_indice(int tipo)
{
    if(TablaT.getName(tipo)!="int"){
        error("El indice debe ser entero");
    }
}

bool Action::equivalentes(int tipo1, int tipo2) {
    // return (TablaT.getBaseType(tipo1) == TablaT.getBaseType(tipo2)) ? true : false;
    return tipo1 == tipo2 ? true : false;
}


string Action::reducir(string dir, int tipoOrg, int tipoDest){
    /*
     * cout<< tipoOrg  << endl;
     * cout<< tipoDest << endl;
     */
    if ( tipoOrg == tipoDest ) {
        return dir;
    } else if (tipoOrg == 1 && tipoDest == 0 ) {
        string temp = nuevaTemporal();
        string cast = "(int)" + dir;
        genCod("=", cast, "", temp);
        return temp;
    } else {
        error("Error de casteo");
        return "error";
    }

}
    //TODO Revisar error de casteo
string Action::ampliar(string dir, int tipoOrg, int tipoDest){
    /*
     * cout<< tipoOrg  << endl;
     * cout<< tipoDest << endl;
     * cout << "--------" << endl;
     */
    if( tipoOrg ==  tipoDest ){
        return dir;
    } else if ( tipoOrg == 0 && tipoDest == 1 ) {
        string temp = nuevaTemporal();
        string cast = "(float)" + dir;
        genCod("=", cast, "", temp);
        return temp;
    } else {
        error("Error de casteo");
        return "error";
    }

}

vector<Cuadrupla> Action::getCodInt(){
    return this->codInt;
}

string Action::nuevaTemporal(){
    numEtq++;
    string temporal = "t" + to_string(numTemp++) + " ";
    return temporal;
}

string Action::nuevaEtiqueta(){
    string etiqueta = "L" + to_string(numEtq++) + " ";
    return etiqueta;
}
