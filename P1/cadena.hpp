#ifndef CADENA_H_
#define CADENA_H_
#include <iterator>


class Cadena{

    public:

        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator <iterator> reverse_iterator;
        typedef std::reverse_iterator <const_iterator> const_reverse_iterator;


        explicit Cadena(unsigned tam=0, char c=' ');
        Cadena(const Cadena& c);
        Cadena(Cadena&& c);
        Cadena(const char* c);
        
        Cadena& operator =(const Cadena& c);
        Cadena& operator =(const char* c);

        //Operador de asignación con semántica de movimiento
        Cadena& operator =(Cadena&& c);
        

        //Cambio de conversión implícita a método de conversión explícita (P1)
        const char* c_str() const;

        unsigned length() const noexcept {return tam_;};
        Cadena& operator +=(const Cadena& c);
        Cadena operator +(const Cadena& c) const;

        //Funciones con iteradores
        //begin
        iterator begin() {return s_;}
        const_iterator begin() const {return s_;}

        //end
        iterator end() {return s_ + tam_;}
        const_iterator end() const {return s_ + tam_;}

        //cbegin. Funciona igual que begin const pero este se "usa" para objetos no constantes
        const_iterator cbegin() const {return s_;}

        //cend. Funciona igual que end const pero este se "usa" para objetos no constantes
        const_iterator cend() const {return s_ + tam_;}

        //rbegin
        reverse_iterator rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

        //rend
        reverse_iterator rend() {return reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

        //crbegin
        const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}

        //crend
        const_reverse_iterator crend() const {return const_reverse_iterator(begin());}


        //Sobrecarga de operadores de comparación
        bool operator ==(const Cadena& c);
        bool operator <(const Cadena& c);
        bool operator >(const Cadena& c);
        bool operator !=(const Cadena& c);
        bool operator <=(const Cadena& c);
        bool operator >=(const Cadena& c);


        //At y sobrecarga de operador []
        char& operator [](unsigned i) {return s_[i];}
        char& operator [](unsigned i) const {return s_[i];}

        char& at(unsigned i);
        char& at(unsigned i) const;

        //Substr
        Cadena substr(int indice,int tamanno) const; 
        ~Cadena();

    private:
        char* s_;
        unsigned tam_;

};

bool operator ==(const char* cad, const Cadena& c);
bool operator <(const char* cad, const Cadena& c);
bool operator >(const char* cad, const Cadena& c);
bool operator !=(const char* cad, const Cadena& c);
bool operator <=(const char* cad, const Cadena& c);
bool operator >=(const char* cad, const Cadena& c);

//Sobrecarga de operador de inserción
std::ostream& operator <<(std::ostream& os,const Cadena& c);

//Sobrecarga de operador de extracción
std::istream& operator >>(std::istream& is,Cadena& c);







#endif
