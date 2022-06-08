#include "../include/TS.hpp"


TS::TS( std::map<std::string, symbols> tabla ) {
	this->table.insert(tabla.begin(), tabla.end());
}

int TS::getType(std::string id){
	auto it = table.find(id);
	return it->second.type;
}

std::string TS::getCategory(std::string id){
	auto it = table.find(id);
	return it->second.category;
}

std::vector<int> TS::getArgs(std::string id){
	auto it = table.find(id);
	return it->second.args;
}

bool TS::existe(std::string id){
	return (this->table.count(id)) ? true : false;
}

void TS::agregar(std::string id, int dir, int tipo, std::string categoria){
	symbols temp;
	temp.dir = dir;
	temp.type = tipo;
	temp.category = categoria;
	this->table.insert({id,temp});
}

std::map<std::string, symbols> TS::getTable(){
	return this->table;
}

