#include "../include/Generator.hpp"
//TODO: Pasar tabla de simbolos y tipos a translate

void Generator::translate(vector<Cuadrupla> code, std::map<std::string, symbols>TablaS, std::map<int, types> TablaT, std::map<string, string> constFloat)
{
  map <string, symbols>::iterator simbolo;
  map <string, string>::iterator cf;

  generateFile("mips");
  file << ".data" << endl;
  for(simbolo = TablaS.begin(); simbolo != TablaS.end(); simbolo++){
    if(simbolo->second.type > 1){
      auto t = TablaT.find(simbolo->second.type);
      file << "\t" << simbolo->first << ": " << ".space " << t->second.size << endl;
    }else
      file <<"\t"<< simbolo->first << ": " << ".word" << endl;
  }

  for (cf = constFloat.begin(); cf != constFloat.end(); cf++){
    file << "\t" << cf->second << ": " << ".float " << cf->first << endl;
  }

  file << ".text" << endl;
  for(std::vector<Cuadrupla>::iterator c = code.begin(); c!= code.end(); ++c){
    auto S = TablaS.find(c->res);
    int tipo = S->second.type;
    if(tipo > 1)
      translate(*c, 1);
    else
      translate(*c, tipo);
  }
  file.close();
}


void Generator::intermedio(vector<Cuadrupla> code,std::map<std::string, symbols>TablaS, std::map<int, types> TablaT, std::map<string, string> constFloat)
{
  map <string, string>::iterator cf;
  map <string, symbols>::iterator simbolo;
  generateFile("i--");
  for(simbolo = TablaS.begin(); simbolo != TablaS.end(); simbolo++){
    string tipo = simbolo->second.type > 1 ? "array" : simbolo->second.type > 0 ? "float" : "int"; 
    file << tipo << " " << simbolo->first << ";" << endl;
  }
  
   for (cf = constFloat.begin(); cf != constFloat.end(); cf++){
    file << "float " << cf->second << " = " << cf->first << ";" << endl;
  }

  for(Cuadrupla c : code){
    if( c.op == "*")
      file <<"\t"<< c.res + " = "+ c.op1 + " " +  c.op + " " + c.op2 << endl;
    else if( c.op == "+")
      file <<"\t"<< c.res + " = "+ c.op1 + " " +  c.op + " " + c.op2 << endl;
    else if(c.op == "label")
      file << c.res << ": "<<endl;
    else if(c.op == "goto")
      file <<"\t"<< c.op << " " << c.res << endl;
    else if(c.op == "if")
      file <<"\t"<< c.op << " " << c.op1 << " "<< c.op2 << " " << c.res << endl;
    else if (c.op == "castF" || c.op == "castI" ) {
      file <<"\t"<< c.res + " = "+ c.op1 + " "   << endl;
    } else if( c.op != ""){
      file <<"\t"<< c.res + " " +  c.op1 + " " +  c.op + " " + c.op2 << endl;
    }
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

void Generator::translate(Cuadrupla c, int tipo = 1)
{
  if(tipo == 0){
    if(c.op == "+"){
      file <<"\tlw $t0, " <<c.op1<<endl;
      file <<"\tlw $t1, " <<c.op2<<endl;
      file <<"\tadd $t2, $t0, $t1"<<endl;
      file <<"\tsw $t2, " <<c.res<<endl;
    } else if (c.op == "*") {
      file <<"\tlw $t0, " <<c.op1<<endl;
      file <<"\tlw $t1, " <<c.op2<<endl;
      file <<"\tmul $t2, $t0, $t1"<<endl;
      file <<"\tsw $t2, " <<c.res<<endl;
    } else if (c.op == "=") {
      file <<"\tlw $t0, " <<c.op2<<endl;
      file <<"\tsw $t0, " <<c.res<<endl;
    }
  } else if(tipo == 1) {
    if(c.op == "+"){
      file <<"\tla $t0, " <<c.op1<<endl;
      file << "\tl.s $f0, (t0)"<<endl;
      file <<"\tla $t1, " <<c.op2<<endl;
      file << "\tl.s $f1, ($t1)"<<endl;
      file <<"\tadd.s $f2, $f0, $f1"<<endl;
      file <<"\ts.s $f2, "<<c.op1<<endl;
    } else if (c.op == "*") {
      file <<"\tla $t0, " <<c.op1<<endl;
      file << "\tl.s $f0, (t0)"<<endl;
      file <<"\tla $t1, " <<c.op2<<endl;
      file << "\tl.s $f1, ($t1)"<<endl;
      file <<"\tmul.s $f2, $f0, $f1"<<endl;
      file <<"\ts.s $f2, "<<c.op1<<endl;
    } else if (c.op == "=") {
      file <<"\tla $t0, " <<c.op2<<endl;
      file <<"\tl.s $f0, ($t0)"<<endl;
      file <<"\ts.s $f0, " <<c.res<<endl;
    }
  }
  
    if (c.op == "if"){
      file <<"\tsw $t0, " <<c.op1<<endl;
      file <<"\tbne $t0, $zero, ." <<c.res<<endl;
    } else if (c.op == "castF"){
      size_t i = c.op1.find(")");
      if( i != std::string::npos) {
        file <<"\tlw $t0, " <<c.op1.substr(i+1)<<endl;
        file <<"\tmtc1 $t0, $f0"<<endl;
        file <<"\tcvt.s.w $f0, $f0"<<endl;
        file <<"\ts.s $f0, ."<<c.res<<endl;
      }
    } else if (c.op == "castI"){
      size_t i = c.op1.find(")");
      if( i != std::string::npos){
        file <<"\tla $0, " <<c.op1.substr(i+1)<<endl;
        file <<"\tl.s $f0, ($0)"<<endl;
        file <<"\tcvt.w.s $f0, $f0"<<endl;
        file <<"\tmfc1 $t0, $f0"<<endl;
        file <<"\tlw $t0, ."<<c.res<<endl;
      }
    } else if (c.op == "goto"){
      file <<"\tb ."<<c.res<<endl;
    } else if (c.op == "label"){
      file <<"."<<c.res<<": "<<endl;
    }

}
