#ifndef __TT_HPP__
#define __TT_HPP__

#include "TS.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>

struct types {
	public:
		std::string name;
		int size;
		int elements;
		int baseType;
    types() = default;
    types(std::string name, int size, int elements, int base);
};

class TT {
    private:
        std::map<int,types> table;
    
    public:
        TT();
        std::string getName(int id);
        int getSize(int id);
        int getElements(int id);
        int getBaseType(int id);
        int agregar(std::string val, int base);
        bool existe(int id);
};

#endif //!__TT_HPP__
