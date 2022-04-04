#include <iostream>


class Vector{

    public:
/*a)*/  explicit Vector(size_t n,double d=0.);
        Vector(std::initializer_list<double> l);
/*c)*/  ~Vector();
/*d)*/  Vector(const Vector& v);
/*e)*/  Vector(Vector&& v);
/*f)*/  double at(size_t i) const;
        double& at(size_t i);
        
    private:
        size_t n;
        double* datos;
    
};

//b)
Vector::Vector(size_t n,double d): n(n), datos(new double[n]){

    for(size_t i=0;i<n;i++){
        datos[i]=d;
    }
}

Vector::Vector(std::initializer_list<double> l):n(l.size()), datos(new double[l.size()]) {

    std::copy(l.begin(),l.end(),datos);

}


//c)
/* No es válido ya que el destructor por defecto genera problemas con atributos declarados
dinámicamente, por lo que es conveniente declarar un destructor */

Vector::~Vector(){

    delete [] datos;

}


//d)

Vector::Vector(const Vector& v): n(v.n), datos(new double[v.n]){

    for(size_t i=0;i<n;i++){
        datos[i]=v.datos[i];
    }

}

//e)

Vector::Vector(Vector&& v): n(v.n), datos(v.datos){

    v.n=0;
    v.datos=nullptr;

}

//f)

double Vector::at(size_t i) const{

    if(i>=n){

        throw std::out_of_range("Índice fuera del rango");

    }else{
        return datos[i];
    }

}

double& Vector::at(size_t i){
    
    if(i>=n){

        throw std::out_of_range("Índice fuera del rango");

    }else{
        return datos[i];
    }

}


class Doble{

    public:
        Doble(double d): dato(d){}
        inline operator double() const {return dato;}

    private:
        double dato;

};