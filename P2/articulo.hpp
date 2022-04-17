#ifndef ARTICULO_H_
#define ARTICULO_H_


#include <iostream>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo{
   
    public:
        Articulo(Cadena ref,Cadena tit, Fecha fecha, double prec, size_t stck=0);

        const Cadena& referencia() const noexcept;
        const Cadena& titulo() const noexcept;
        const Fecha& f_publi() const noexcept;
        double precio() const noexcept;
        double& precio();
        size_t stock() const noexcept;
        size_t& stock();
        ~Articulo();

   
    private:
        const Cadena referencia_;
        const Cadena titulo_;
        const Fecha f_publi_;
        double precio_;
        size_t stock_;


};


std::ostream& operator <<(std::ostream& os,const Articulo& art);

inline const Cadena& Articulo::referencia() const noexcept {return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept {return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept {return f_publi_;}
inline double Articulo::precio() const noexcept {return precio_;}
inline double& Articulo::precio() {return precio_;}
inline size_t Articulo::stock() const noexcept {return stock_;}
inline size_t& Articulo::stock() {return stock_;}


#endif