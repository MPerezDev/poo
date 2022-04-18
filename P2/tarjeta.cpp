#include <iostream>
#include <string.h>
#include <iomanip>
#include "tarjeta.hpp"


//Numero

Numero::Numero(const Cadena& cad): numero_(cad){

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

    return numero_.c_str();

}

bool operator <(const Numero& num1, const Numero& num2){

    return num1.numero_ < num2.numero_;

}


//Tarjeta

Tarjeta::Tarjeta(const Numero& num, Usuario& u, const Fecha& fec): numero_(num), titular_(&u), caducidad_(fec){

    activa_ = true;

    if(fec < Fecha()){

        throw Caducada(fec);

    }

    if(!lista_tarjetas.insert(Cadena(num)).second){
        throw Num_duplicado(num);
    }

    u.es_titular_de(*this);

}

Tarjeta::~Tarjeta(){

    titular_->no_es_titular_de(*this);

}

const Tarjeta::Tipo Tarjeta::tipo() const noexcept{

    int j=0,i=0;
    char aux[2];
    Cadena cadAux(numero_);

    do{
        
        if(isdigit(cadAux[i])){
            aux[j] = cadAux[i];
            j++;
        }
        i++;

    }while(j<2 && i<=cadAux.length());

    if(aux[0]==3){
        if(aux[1]==4 || aux[1]==7){
            return Tipo::AmericanExpress;
        }else{
            return Tipo::JCB;
        }
    }else if(aux[0]==4){
        return Tipo::VISA;
    }else if(aux[0]==5){
        return Tipo::Mastercard;
    }else if(aux[0]==6){
        return Tipo::Maestro;
    }else{
        return Tipo::Otro;
    }


}

bool Tarjeta::activa(bool aux){

    activa_ = aux;
    return activa_;

}

void Tarjeta::anula_titular(){

    titular_ = nullptr;
    activa(false);

}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo){
    switch(tipo)
    {
        case 0: 
            os << "Otro"; 
            break;
        case 1: 
            os << "VISA"; 
            break;
        case 2: 
            os << "Mastercard"; 
            break;
        case 3: 
            os << "Maestro";
            break;
        case 4: 
            os << "JCB"; 
            break;
        case 5: 
            os << "AmericanExpress"; 
            break;
        default: 
            os << "Tipo desconocido"; 
            break;
    }

    return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& tarjeta){
    Cadena cadAux = tarjeta.titular()->nombre() + " " + tarjeta.titular()->apellidos();


    for(size_t i=0; i< cadAux.length(); i++)
    {
        cadAux[i] = toupper(cadAux[i]);
    }

    os << tarjeta.tipo() << "\n" << Cadena(tarjeta.numero()) << "\n" << cadAux << "\nCaduca: ";

    Cadena mes;
    if (tarjeta.caducidad().mes() < 10){
        os << 0 << tarjeta.caducidad().mes();
    }
    else{
        os << tarjeta.caducidad().mes();
    }

    os << "/" << (tarjeta.caducidad().anno() % 100) << std::endl;

    return os;
}


bool operator <(const Tarjeta& t1, const Tarjeta& t2){

    return t1.numero() < t2.numero();
    
}

