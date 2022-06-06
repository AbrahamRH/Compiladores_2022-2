#include <iostream>
#include <fstream>
#include "../include/Parser.hpp"
#include "../include/Lexer.hpp"

using namespace std;
int main(int argc, char *argv[])
{
	std::cout << "mi primer compilador!" << std::endl;
	if( argc < 2 ){
		cout << "ERROR: Falta nombre del archivo" << endl;
	}

	ifstream archivo;
	archivo.open(argv[1]);
	if(!archivo.is_open()){
		cout<<"ERROR: El archivo " << argv[1] <<" no se puede abrir."<< endl;
		exit(EXIT_FAILURE);
	}

	Lexer lexer(&archivo);
	Parser parser(&lexer);

	if( parser.parse() ){
		cout << "La cadena es aceptada" << endl;
	} else {
		cout << "La cadena no es aceptada" << endl;
	}
	return 0;

}
