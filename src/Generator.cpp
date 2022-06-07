#include "../include/Generator.hpp"
//TODO: Pasar tabla de simbolos y tipos a translate
//TODO: hacer que el código intermedio se vea lindo 

void Generator::translate(vector<Cuadrupla> code)
{
  generateFile("mips");
  for(std::vector<Cuadrupla>::iterator c = code.begin(); c!= code.end(); ++c){
    translate(*c,0);
  }
  file.close();
}


void Generator::intermedio(vector<Cuadrupla> code)
{
  generateFile("i--");
  for(Cuadrupla c : code){
    file << c.res + " = " + c.op1 + " " +  c.op + " " + c.op2 << endl;
  }
  file.close();
}


void Generator::setFilename(string filename)
{
  this->filename = filename;
}

void Generator::generateFile(string ext){
  int found = filename.find(".");
  string name = filename.substr(0,found);
  name += "." + ext;
  file.open(name, ios::trunc);
  if(!file.is_open()){
		cout<<"ERROR: El archivo " << name <<" no se puede abrir."<< endl;
		exit(EXIT_FAILURE);
  }
}

//TODO: terminarla
void Generator::translate(Cuadrupla c, int tipo)
{
  if( c.op == "+"){
    file <<"\tlw $t0, " <<c.op1<<endl;
    file <<"\tlw $t1, " <<c.op2<<endl;
    file <<"\tadd $t2, $t0, $t1"<<endl;
    file <<"\tsw $t2, " <<c.res<<endl;
  } else if (c.op == "if"){
    file <<"\tlw $t0, " <<c.op1<<endl;
    file <<"\tbne $t0, $zero, " <<c.res<<endl;
  }

  cout << c.op << endl;

}
