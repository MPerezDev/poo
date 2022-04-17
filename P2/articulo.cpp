#include "articulo.hpp"


Articulo::Articulo(Cadena ref,Cadena tit, Fecha fecha, double prec, size_t stck): referencia_(ref), titulo_(tit), f_publi_(fecha), precio_(prec), stock_(stck) {}

Articulo::~Articulo(){}

std::ostream& operator <<(std::ostream& os,const Articulo& art){
    return os << "[" << art.referencia() << "] \"" << art.titulo() << "\", " << art.f_publi().anno() << ". " << art.precio() << " €";

}


