#ifndef CADENA_H_
#define CADENA_H_


class Cadena{

    public:
        explicit Cadena(unsigned tam=0, char c=' ');
        Cadena(const Cadena& c);
        Cadena(const char* c);
        
        Cadena& operator =(const Cadena& c);
        Cadena& operator =(const char* c);
        

        operator const char*() const;
        unsigned length() const noexcept {return tam_;};
        Cadena& operator +=(const Cadena& c);
        Cadena operator +(const Cadena& c) const;


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









#endif
