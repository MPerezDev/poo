
#ifndef TARJETA_H_
#define TARJETA_H_

#include <iostream>
#include <unordered_set>
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

        Cadena numero_;

};

class Tarjeta{

    public:
        enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
        typedef std::unordered_set<Cadena> Listas;

        Tarjeta(const Numero& num, Usuario& u, const Fecha& fec);

        class Caducada{
            public:
                Caducada(Fecha f): caducada_{f} {}
                Fecha cuando() const noexcept {return caducada_;}
            private:
                Fecha caducada_;

        };

        class Num_duplicado{
            public:
                Num_duplicado(Numero num): num_{num} {}
                Numero que() const noexcept {return num_;}
            private:
                Numero num_;

        };

        class Desactivada;

        const Numero& numero() const noexcept;
        const Usuario& titular() const noexcept;
        const Fecha& caducidad() const noexcept;
        const bool activa() const noexcept;
        const Tipo tipo() const noexcept;
        bool activa(bool aux=true);

        void anula_titular();

        ~Tarjeta();

    private:
        const Numero numero_;
        mutable Usuario* titular_;
        const Fecha caducidad_;
        bool activa_;
        static Listas lista_tarjetas;




};



inline const Numero& Tarjeta::numero() const noexcept {return numero_;};
inline const Usuario& Tarjeta::titular() const noexcept {return &titular_;};
inline const Fecha& Tarjeta::caducidad() const noexcept {return caducidad_;};
inline const bool Tarjeta::activa() const noexcept {return activa_;};

bool operator <(const Tarjeta& t1, const Tarjeta& t2);

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
std::ostream& operator <<(std::ostream& os, const Tarjeta& tarjeta);


#endif