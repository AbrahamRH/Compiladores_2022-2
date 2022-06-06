#ifndef __TS_HPP__
#define __TS_HPP__

#include <iostream>
#include <map>
#include <vector>
#include <string>

struct symbols {
	public:
		int dir;
		int type;
		std::string category;
		std::vector<int> args;
};

class TS {
	private:
		std::map<std::string,symbols> table; 

	public:
		TS() = default;
		TS( std::map<std::string, symbols> );
		int getType(std::string id);
		std::string getCategory(std::string id);
		std::vector<int> getArgs(std::string id);
		bool existe(std::string id);
		void agregar(std::string id, int dir, int tipo, std::string categoria);

};


#endif //!__TS_HPP__
