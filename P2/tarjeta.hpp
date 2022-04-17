
#ifndef TARJETA_H_
#define TARJETA_H_

#include <iostream>
#include "articulo.hpp"
#include "../P1/cadena.hpp"

bool luhn(const Cadena& num);

class Clave;
class Usuario;

class Numero{

    public:

        enum Razon {LONGITUD,DIGITOS,NO_VALIDO};
        Numero(const Cadena& cad);

        //Clase de excepción
        class Incorrecto{
            public:
                Incorrecto(Razon r): razon_{r} {}
                Razon razon() const noexcept {return razon_;}
            private:
                Razon razon_;

        };

        operator const char*() const;
        friend bool operator <(const Numero& num1, const Numero& num2);

    private:

        Cadena numero;

};

class Tarjeta{

};


#endif