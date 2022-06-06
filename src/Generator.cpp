#include "../include/Generator.hpp"

void Generator::translate(vector<Cuadrupla> code)
{
  for(std::vector<Cuadrupla>::iterator c = code.begin(); c!= code.end(); ++c){
    translate(*c,0);
  }
}

//TODO: terminarla
//que representa tipo?

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
}
