#include <iostream>
#include <string.h>
#include "tarjeta.hpp"

Numero::Numero(const Cadena& cad): numero(cad){

    int j=0;
    char* aux = new char[cad.length()];
    for(int i = 0; i <= cad.length(); i++){

            if(cad[i]!=' ' && cad[i]!='\v' && cad[i]!='\r' && cad[i]!='\t' && cad[i]!='\f'){
                aux[j]==cad[i];
                j++;
            }       

    }
    
    if( strlen(aux) < 13 || strlen(aux) > 19){

        throw Numero::Incorrecto(Razon::LONGITUD);

    }

    for(int i = 0; i<= strlen(aux); i++){

        if(!isdigit(aux[i])){

            throw Numero::Incorrecto(Razon::DIGITOS);

        } 

    }

    if(!luhn(Cadena(aux))){

        throw Numero::Incorrecto(Razon::NO_VALIDO);

    }
        

}

Numero::operator const char*() const{

    return numero.c_str();

}

bool operator <(const Numero& num1, const Numero& num2){

    return num1.numero < num2.numero;

}

