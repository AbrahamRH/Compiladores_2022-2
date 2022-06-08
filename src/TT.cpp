#include "../include/TT.hpp"

TT::TT( ) {
    types type = types("int", 4, -1, -1);
    table[0] = type;
    type = types("float", 4, -1, -1);
    table[1] = type;
}

std::string TT::getName(int id){
    auto name = table.find(id);
    return  name->second.name;
}

int TT::getSize(int id){
    auto tam = table.find(id);
    return tam->second.size;
}

int TT::getElements(int id){
    return table[id].elements;
}

int TT::getBaseType(int id){
    auto baseType = table.find(id);
    return  baseType->second.baseType;
}

bool TT::existe(int id){
	return (this->table.count(id)) ? true : false;
}

int TT::agregar(std::string val, int base){
    int size = stoi(val)*getSize(base);
    types tmp = types("array", size, stoi(val), base);
    int id = table.size();
    table[id] = tmp;
    return id;
    
}

types::types(std::string name, int size, int elements, int base){
    this->name = name;
    this->size = size;
    this->elements = elements;
    this->baseType = base;
}

std::map<int,types> TT::getTable(){
    return this->table;
}