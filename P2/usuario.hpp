#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "../P1/cadena.hpp"
#include "articulo.hpp"
//#include <unistd.h>
class Tarjeta;
class Numero;


class Clave{

    public:
        Clave(const char* passwd);
        enum Razon{CORTA,ERROR_CRYPT};

        class Incorrecta{ //Creamos una clase para las excepciones.
            public:
                Incorrecta(Razon r): razon_{r} {}
                Razon razon() const noexcept {return razon_;}
            private:
                Razon razon_;

        };
        const Cadena clave() const noexcept;
        bool verifica(const char* cad);


    private:
        Cadena clave_;  

};

class Usuario{

    public:

        typedef std::map<Numero,Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*,unsigned int> Articulos;

        Usuario(Cadena id, Cadena nombre, Cadena apellidos, Cadena direccion, Clave contrasenna);
        Usuario(const Usuario& u) = delete;
        ~Usuario();

        //Clase de excepción
        class Id_duplicado{
            public:
                Id_duplicado(Cadena cad): idd_{cad} {}
                Cadena idd() const noexcept {return idd_;}
            private:
                Cadena idd_;

        };

        const Cadena& id() const noexcept;
        const Cadena& nombre() const noexcept;
        const Cadena& apellidos() const noexcept;
        const Cadena& direccion() const noexcept;
        const Tarjetas& tarjetas() const noexcept;
        const Articulos& compra() const noexcept;

        void es_titular_de(const Tarjeta& tarjeta);
        void no_es_titular_de(const Tarjeta& tarjeta);

        void compra(const Articulo& articulo, size_t cantidad=1);

        unsigned int n_articulos() const noexcept;

    private:
        const Cadena id_;
        const Cadena nombre_;
        const Cadena apellidos_;
        const Cadena direccion_;
        Clave contrasenna_;
        Tarjetas tarjetas_;
        Articulos compra_;
        static std::unordered_set<Cadena> lista_id;

};

inline const Cadena Clave::clave() const noexcept{return clave_;}
inline const Cadena& Usuario::id() const noexcept{return id_;}
inline const Cadena& Usuario::nombre() const noexcept{return nombre_;}
inline const Cadena& Usuario::apellidos() const noexcept{return apellidos_;}
inline const Cadena& Usuario::direccion() const noexcept{return direccion_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const noexcept{return tarjetas_;}
inline const Usuario::Articulos& Usuario::compra() const noexcept{return compra_;}

inline unsigned int Usuario::n_articulos() const noexcept{return compra_.size();}
