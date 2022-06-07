#include "../include/Parser.hpp"
//#include std::string;

Parser::Parser(Lexer *lexer, string filename = "out")
{
    tokens = {
        {TOK_ID,"id"},
        {TOK_NUM,"num"},
        {TOK_MUL,"*"},
        {TOK_MAS,"+"},
        {TOK_INT,"int"},
        {TOK_FLOAT,"float"},
        {TOK_DO,"do"},
        {TOK_WHILE,"while"},
        {TOK_IF,"if"},
        {TOK_ELSE,"else"},
        {TOK_COMA,","},
        {TOK_PYC,";"},
        {TOK_ASIG,"="},
        {TOK_LPAR,"("},
        {TOK_RPAR,")"},
        {TOK_LCOR,"["},
        {TOK_RCOR,"]"},
    };
    this->lexer = lexer;
    this->gen.setFilename(filename);

    TOKEN tmp;

    do { 
        tmp = (TOKEN)this->lexer->yylex();
        tokens_enum.push(tmp);
        tokens_string.push(this->lexer->getVal());
        tokens_numType.push(this->lexer->getType());
        tokens_lines.push(this->lexer->getLine());
    } while( tmp != 0 );

    token = tokens_enum.front();
    
}

TOKEN Parser::getCurrentToken(){
    tokens_enum.pop();
    tokens_string.pop();
    tokens_numType.pop();
    tokens_lines.pop();
    TOKEN top = tokens_enum.front();
    return top;
}


Parser::Parser(){
    
}

bool Parser::parse(){
    p();
    gen.translate(action.getCodInt());
    gen.intermedio(action.getCodInt());
    if(token == TOK_EOF){
    }
    return token == TOK_EOF;
}

void Parser::eat(TOKEN token_eat){
    if( token == token_eat ){  
        token = getCurrentToken();
    } else {
        error("Se encontro " + tokens[token] +  " token y se esperaba " + tokens[token_eat] );
    }
}

void Parser::error(string msg){
    cout<<"ERROR SEMÁNTICO: "<<msg<<endl;
    cout<<"ERROR ENCONTRADO EN LA LINEA: "<<to_string(tokens_lines.front())<<endl;
    exit(EXIT_FAILURE);
}

void Parser::p()
{
    d();
    r();
}

void Parser::d()
{
    if(token== TOK_INT || token ==TOK_FLOAT){
        int Ttipo = t();
        l(Ttipo);
        eat(TOK_PYC);
        d();
    }else
        return;
}

int Parser::t()
{
    int Btipo = b();
    int Ttipo = a(Btipo);
    return Ttipo;
}

int Parser::b(){
    if(token == TOK_INT){
        eat(TOK_INT);
        return 0;
    }
    else if (token == TOK_FLOAT)
    {
        eat(TOK_FLOAT);
        return 1;
    }
    else
    {
        error("Se esperaba int o float en la linea.");
    }
}

int Parser::a(int Abase){
    string numVal;
    int numType;
    if(token == TOK_LCOR){
        eat(TOK_LCOR);
        int numType = lexer->getType();
        std::string numVal = tokens_string.front();
        eat(TOK_NUM);
        eat(TOK_RCOR);
        int A1tipo = a(Abase);
        //TODO
        int Atipo = action.agregarTipo(numVal , A1tipo);
        // int Atipo = action.validarDimensionArreglo(numType, numVal, A1tipo);
        return Atipo;
    }else{
        return Abase;
    }
}

void Parser::l(int ltipo){
    string idVal;
    idVal = tokens_string.front(); //id
    eat(TOK_ID);
    action.agregarSimbolo(idVal, ltipo, "variable");
    l_(ltipo);
}

void Parser::l_(int tipo)
{
    string idVal;    
    if(token == TOK_COMA){
        eat(TOK_COMA);
        idVal = tokens_string.front();
        eat(TOK_ID);
        action.agregarSimbolo(idVal, tipo, "variable");
        l_(tipo);
    }
}

void Parser::r()
{
    if(token == TOK_ID || token == TOK_IF || token==TOK_DO || token == TOK_WHILE)
    {
        s();
        r_();
    }
}

void Parser::r_()
{
    if(token == TOK_ID || token == TOK_IF || token==TOK_DO || token == TOK_WHILE)
    {
        s();
        r_();
    }
}

void Parser::s(){
    string Linicio, Ltrue, Lfalse;
    
    if(token == TOK_ID)
    {
        string idVal = tokens_string.front();
        eat(TOK_ID);
        action.existe(idVal);
        c(idVal);
        // eat(TOK_PYC);
    }else if(token == TOK_IF){
        eat(TOK_IF);
        eat(TOK_LPAR);
        e();
        eat(TOK_RPAR);
        s();
        z();
    }else if(token == TOK_WHILE){
        Linicio = action.nuevaEtiqueta();
        Ltrue = action.nuevaEtiqueta();
        Lfalse = action.nuevaEtiqueta();
        eat(TOK_WHILE);
        eat(TOK_LPAR);
        expresion E = e();
        eat(TOK_RPAR);
        action.genCod("label", "", "", Linicio);
        action.genCod("if", E.dir, "goto", Ltrue);
        action.genCod("goto", "", "", Lfalse);
        s();        
        action.genCod("goto", "", "", Linicio);
        action.genCod("label", "", "", Lfalse);
    }else if(token == TOK_DO){
        Ltrue = action.nuevaEtiqueta();
        Lfalse = action.nuevaEtiqueta();
        eat(TOK_DO);
        s();
        eat(TOK_WHILE);
        eat(TOK_LPAR);
        expresion E = e();
        eat(TOK_RPAR);
        eat(TOK_PYC);
        action.genCod("label", Ltrue, "Codigo", Linicio);
        action.genCod("if", E.dir, "goto", Ltrue);
        action.genCod("label", "", "", Lfalse);
        
    }else{
        error("Se esperaba id o if o while o do");
    }
}

void Parser::z(){
    string Lfin, Lfalse;
    if(token == TOK_ELSE){
        Lfin = action.nuevaEtiqueta();
        Lfalse = action.nuevaEtiqueta();
        action.genCod("goto", "", "", Lfin);
        action.genCod("label", "", "", Lfalse);
        eat(TOK_ELSE);
        s();
        action.genCod("label", "", "", Lfin);   
    } else{
        Lfalse = action.nuevaEtiqueta();
        action.genCod("label", "", "", Lfalse);
    }
}



void Parser::c(string id)
{
    expresion E, Y;
    if(token == TOK_ASIG)
    {
        eat(TOK_ASIG);
        E = e();
        action.asignacion(id, E);
    }else if(token == TOK_LCOR){
        expresion Yh;
        Yh.dir = id;
        Yh.tipo = action.TablaS.getType(id);        
        Y = y(Yh);
        eat(TOK_ASIG);
        E = e();
        action.asignacion(id, Y.dir, E);
    }
    eat(TOK_PYC);
}

expresion Parser::e()
{
    expresion G = g();
    expresion E_ = e_(G);
    return E_;
}

expresion Parser::e_(expresion E_)
{
    
    if(token == TOK_MAS)
    {
        eat(TOK_MAS);
        expresion G =g();
        expresion E_1h;
        action.equivalentes(E_.tipo, G.tipo);
        E_1h.tipo = action.maximo(E_.tipo, G.tipo);
        E_1h.dir = action.nuevaTemporal();
        expresion E_1s = e_(E_1h);
        //TODO: Revisas gramatica
        string op1 = action.ampliar(E_1h.dir, E_1h.tipo, E_1h.tipo);
        string op2 = action.ampliar(G.dir, G.tipo, E_1h.tipo);
        action.genCod("+",op1, op2, E_1s.dir);
        return E_1s;
    }else{
        return E_;
    }
}

/*
*Listo g y g_
*/

expresion Parser::g()
{
    expresion G_ = f();
    expresion g = g_(G_);
    return g;
}

expresion Parser::g_(expresion G_){
    if(token == TOK_MUL){
        eat(TOK_MUL);
        expresion F = f();
        expresion G_1h;
        G_1h.tipo = action.maximo(G_.tipo, F.tipo);
        G_1h.dir = action.nuevaTemporal();
        expresion G_1s = g_(G_1h);
        string op1 = action.ampliar(G_.dir, G_.tipo, G_1h.tipo);
        string op2 = action.ampliar(F.dir, F.tipo, G_1h.tipo);
        action.genCod("*", op1, op2, G_1h.dir);
        return G_1h;
    }else
        return G_;
}


expresion Parser::f(){
    expresion F;
    if(token == TOK_LPAR){
        eat(TOK_LPAR);
        F = e();
        eat(TOK_RPAR);
        return F;
    }else if(token == TOK_NUM){
        F.dir = tokens_string.front();
        F.tipo = tokens_numType.front();
        eat(TOK_NUM);
        return F;
    }else if(token == TOK_ID){
        string idVal = tokens_string.front();
        eat(TOK_ID);
        action.existe(idVal);
        F.dir = idVal;
        F.tipo = action.TablaS.getType(idVal);
        F = f_(F);
        return F;
    }else 
        error("El id no fue definido");
}

expresion Parser::f_(expresion F_){
    if(token == TOK_LCOR){
        expresion Y = y(F_);
        stringstream ss;
        ss<<F_.dir<<"["<<Y.dir<<"]";
        expresion F_;
        F_.dir = ss.str();
        F_.tipo = Y.tipo;
        return F_;
    }else{
        return F_;
    }
}

expresion Parser::y(expresion id){
    eat(TOK_LCOR);
    expresion E = e();
    eat(TOK_RCOR);    
    action.validar_array(id.tipo);
    action.validar_indice(E.tipo);
    arreglo Y_h;
    Y_h.tipo =action.TablaT.getBaseType(id.tipo);
    Y_h.dir = action.nuevaTemporal();
    Y_h.tam = action.TablaT.getSize(Y_h.tipo);
    arreglo Y_s = y_(Y_h);
    expresion Y;
    Y.dir = Y_s.dir;
    Y.tipo = Y_s.tipo;
    return Y;
}

arreglo Parser::y_(arreglo Y_)
{
    if(token == TOK_LCOR){
        eat(TOK_LCOR);
        expresion E = e();
        eat(TOK_RCOR);
        action.validar_array(Y_.tipo);
        action.validar_indice(E.tipo);
        arreglo Y_1h;
        Y_1h.tipo =action.TablaT.getBaseType(Y_.tipo);
        string t = action.nuevaTemporal();
        Y_1h.dir = action.nuevaTemporal();
        Y_1h.tam = action.TablaT.getSize(Y_1h.tipo);
        arreglo Y_1s = y_(Y_1h);
        stringstream ss;
        ss<<Y_1h.tam;
        action.genCod("*",E.dir, ss.str(), t);
        action.genCod("+",Y_1s.dir, t, Y_1h.dir);
        return Y_1s;
    }else{
        return Y_;
    }
}

int Action::maximo(int tipo1,int tipo2){
    return (tipo1 > tipo2) ? tipo1 : tipo2;
}

int Action::minimo(int tipo1,int tipo2){
    return (tipo1 < tipo2) ? tipo1 : tipo2;
}

