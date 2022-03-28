#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include "cadena.hpp"

//Es más elegante poner la linea 10 y la 11 en la cabecera
Cadena::Cadena(unsigned tam, char c){

    tam_ = tam;
    s_ = new char[tam_+1];
    
    for(int i=0; i < tam_; i++){

        s_[i]=c;

    }
      
    s_[tam_] = '\0';

}

Cadena::Cadena(const Cadena& c): tam_(c.tam_){

    s_ = new char[tam_+1];
    strcpy(s_,c.s_);

}

Cadena::Cadena(const char* c){

    tam_ = strlen(c);
    s_ = new char[tam_+1];
    strcpy(s_,c);

}

Cadena::operator const char*() const{

    return s_;

}

//Operadores de asignación
Cadena& Cadena::operator =(const Cadena& c){


    tam_ = c.tam_;
    s_ = new char[tam_+1];
    strcpy(s_,c.s_);

    return *this;

}

Cadena& Cadena::operator =(const char* c){

    tam_=strlen(c);
    s_ = new char[tam_+1];
    strcpy(s_,c);

    return *this;

}

Cadena& Cadena::operator +=(const Cadena& c){

    tam_ += c.tam_;
    strcat(s_,c.s_);

    return *this;

}

Cadena Cadena::operator +(const Cadena& c) const{

    Cadena aux(*this); //Copiamos la cadena-l
    aux += c; //Hacemos sobrecarga para concatenar la cadena-l con la cadena c
    
    return aux;

}

//Operadores de comparación (cadena-cadena y cadena-char)(cadena-char lo hace porque el compilador recurre al constructor de cadena de manera implícita)
bool Cadena::operator ==(const Cadena& c){

    if(strcmp(s_,c.s_)==0) return true;
    else return false;

}

bool Cadena::operator <(const Cadena& c){

    if(strcmp(s_,c.s_)<0) return true;
    else return false;

}

bool Cadena::operator >(const Cadena& c){

    if(strcmp(s_,c.s_)>0) return true;
    else return false;

}

bool Cadena::operator !=(const Cadena& c){

    if(strcmp(s_,c.s_)!=0) return true;
    else return false;

}

bool Cadena::operator <=(const Cadena& c){

    if(strcmp(s_,c.s_)<=0) return true;
    else return false;

}

bool Cadena::operator >=(const Cadena& c){

    if(strcmp(s_,c.s_)>=0) return true;
    else return false;

}


//Comparador char-cadena
bool operator ==(const char* cad, const Cadena& c){

    Cadena aux(cad);
    return aux == c;

}

bool operator <(const char* cad, const Cadena& c){

    Cadena aux(cad);
    return aux < c;

}

bool operator >(const char* cad, const Cadena& c){

    Cadena aux(cad);
    return aux > c;

}

bool operator !=(const char* cad, const Cadena& c){

    Cadena aux(cad);
    return aux != c;

}

bool operator <=(const char* cad, const Cadena& c){

    Cadena aux(cad);
    return aux <= c;

}

bool operator >=(const char* cad, const Cadena& c){

    Cadena aux(cad);
    return aux >= c;

}


char& Cadena::at(unsigned i){

    if(i<tam_){
        return s_[i];
    }else{
        throw std::out_of_range("Fuera de rango");
    }


}
char& Cadena::at(unsigned i) const{
        
    if(i<tam_){
        return s_[i];
    }else{
        throw std::out_of_range("Fuera de rango");
    }


}

Cadena Cadena::substr(int indice,int tamanno) const{

    if(indice + tamanno <= tam_ && tamanno > 0 && indice >=0 && indice <= tam_){

        Cadena aux(tamanno);
        strncpy(aux.s_, s_+indice ,tamanno);
        aux.s_[aux.tam_] = '\0';
        return aux;


    }else{
        throw std::out_of_range("Substr fallido");
    }

}


Cadena::~Cadena(){

    

}
