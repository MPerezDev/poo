#include "usuario.hpp"
#include <string>

//#include <unistd.h>


Clave::Clave(const char* passwd){

    if(strlen(passwd)<5){
        
        throw Incorrecta(Razon::CORTA);

    }

    const char* aux = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char sal[2] = {aux[rand() % 64],aux[rand() % 64]};

    if(crypt(passwd,sal)==NULL){
        throw Incorrecta(Razon::ERROR_CRYPT);
    }

    clave_ = crypt(passwd,sal);

}


bool Clave::verifica(const char* cad){

    return strcmp(crypt(cad,clave_.c_str()),clave_.c_str())==0;

}


Usuario::Usuario(Cadena id, Cadena nombre, Cadena apellidos, Cadena direccion, Clave contrasenna): id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), contrasenna_(contrasenna) {

    if(!lista_id.insert(id).second){
        throw Id_duplicado(id);
    }

}

Usuario::~Usuario(){

    for(auto it=tarjetas_.begin(); it!=tarjetas_.end(); it++){

        it->second->anula_titular();

    }
    Cadena aux(id_);
    lista_id.erase(aux);

}

void Usuario::es_titular_de(const Tarjeta& tarjeta){

    tarjetas_[tarjeta.numero()] = &tarjeta;

}


void Usuario::no_es_titular_de(const Tarjeta& tarjeta){

    tarjetas_.erase(tarjeta.numero());
    
}