#include "usuario.hpp"
#include <string.h>
#include <iomanip>
#include <unistd.h>


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

void Usuario::compra(const Articulo& articulo, unsigned int cantidad){

    if(cantidad==0){
        compra_.erase(articulo);
    }else{
        compra_[articulo] = cantidad;
    }

}

std::ostream& operator <<(std::ostream& os,const Usuario& u){

    os << u.id_ << "[" << u.contrasenna_.clave() << "]" << u.nombre_ << u.apellidos_ << std::endl << u.direccion_ << std::endl << "Tarjetas:" << std::endl;

    for(auto it=u.tarjetas_.begin(); it!=u.tarjetas_.end(); it++){

        os << it->second << std::endl;

    }

    return os;

}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u){

    os << "Carrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << std::endl;

    os << "Cant.Artículo"<< std::endl << std::setw(50) << std::setfill('=') << '\n' << std::setfill(' ');



        for(auto it = u.compra().begin(); it != u.compra().end(); it++){

            os << std::setw(4) << it->second << "    " << it->first << std::endl;

        }

    return os;
    

}
