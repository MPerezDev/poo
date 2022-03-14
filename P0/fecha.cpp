#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fecha.hpp"

Fecha::Fecha(int d,int m, int a): dia_(d), mes_(m), anno_(a){ //Asignamos los valores

    fechaSistema(); //Comprobamos si alguno de los atributos debe ser sustituido por los de la fecha actual del sistema

}

//Constructor de copia no hace falta, se coge automáticamente con el constructor por defecto
Fecha::Fecha(const Fecha& f): dia_(f.dia_), mes_(f.mes_), anno_(f.anno_){}
//Constructor a partir de cadena
Fecha::Fecha(const char* cadena){

    int dia,mes,anno; //Declaramos estas variables, que son las que van a contener los valores de la cadena

    if(sscanf(cadena,"%d/%d/%d", &dia, &mes, &anno) != 3){ //Con sscanf obtenemos los valores de la cadena
        throw Invalida("Fecha incorrecta"); //Lanzamos excepción en caso de que no tengamos fecha con formato correcto
    }else{

        dia_ = dia;
        mes_ = mes;
        anno_ = anno;

        fechaSistema();
        comprobarFecha(); //Hacemos las comprobaciones habituales sobre el ímplicito, ya que los valores han sido copiados.
    }

}

//Añadir fecha actual del sistema en caso de que un dato no esté bien
void Fecha::fechaSistema(){

    std::time_t fechaSFormato = std::time(nullptr); //cogemos la fecha actual del sistema
    std::tm* fechaCFormato = std::localtime(&fechaSFormato); //Transformamos la fecha obtenida, guardándola
                                                        //en el struct std::tm, que tiene unas cuantas variables que vamos a usar ahora
    if(dia_==0) dia_ = fechaCFormato->tm_mday; //tm_mday tiene el dia del mes en el que estamos
    if(mes_==0) mes_ = fechaCFormato->tm_mon + 1; //tm_mon cuenta los meses del 0 al 11, por lo que le sumamos 1
    if(anno_==0) anno_ = fechaCFormato->tm_year + 1900; //tm_year cuenta los años desde 1900, por eso le sumamos esta cantidad

}

//Sobrecarga de asignación =
Fecha& Fecha::operator =(const Fecha& f){

    dia_ = f.dia_;
    mes_ = f.mes_;
    anno_ = f.anno_;

    return *this;

}

//Con este método comprobamos que la fecha esté dentro de los valores correctos
void Fecha::comprobarFecha(){

    int bisiesto = static_cast<int>(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0));
    //Usamos static_cast para convertir el resultado de la comprobación para saber si el año en cuestión es bisiesto
    //El resultado de la comprobación es un bool y lo cambiamos a un int

    if(mes_ < 1 || mes_ > 12){  //Comprobamos que el mes esté entre 1 y 12, si no es así lanzamos una excepción
        throw Invalida ("Mes incorrecto");
    }

    if(mes_ == 2){ //Comprobamos que el día esté entre los valores permitidos según el mes (cubrimos el caso de que se trate de un año bisiesto)
        if(dia_ < 1 || dia_ > dias[mes_] + bisiesto){
            throw Invalida ("Dia incorrecto");
        }
    }else if(dia_ < 1 || dia_ > dias[mes_]){
        throw Invalida ("Dia incorrecto");
    }
    
    if(anno_ < AnnoMin || anno_ > AnnoMax){ //Comprobamos que el año introducido está dentro los valores permitidos
        throw Invalida ("Anno incorrecto");
    }

}

//Sobrecarga de operador <<
std::ostream& operator <<(std::ostream& os, Fecha& f){

    const char dias_[7][10] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
    const char meses_[12][15] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    //Con estos cálculos obtenemos el día de la semana
    int result1=(f.anno_-1)%7;
    int result2=(f.anno_-1)/4;
    int result3=(3*(((f.anno_-1)/100)+1))/4;
    int result4=(result2-result3)%7;
    int result5=f.dia_%7;
    int diasem=(result1+result4+f.mes_+result5)%7;

    return os << dias_[diasem] << " " << f.dia_ << " de " << meses_[f.mes_ - 1] << " de " << f.anno_;



}


//Sobrecarga de operadores. Asignaciones

//Preincremento
Fecha& Fecha::operator ++(){

    dia_++;
    if(dia_ > dias[mes_]){
        dia_ = 1;
        mes_++;
        if(mes_ > 12){
            mes_ = 1;
            anno_++;
        }
    }

    comprobarFecha();

    return *this;
    
}

//Postincremento
Fecha Fecha::operator ++(int){

    Fecha f = *this;
    (*this)++;
    return f;

}

//Predecremento
Fecha& Fecha::operator --(){

    dia_--;
    if(dia_ <= 0){
        dia_ = dias[mes_-1];
        mes_--;
        if(mes_ <= 0){
            mes_ = 12;
            anno_--;
        }

    }

    comprobarFecha();
    return *this;

}

//Postdecremento
Fecha Fecha::operator --(int){

    Fecha f = *this;
    (*this)--;
    return f;

}

//Suma
Fecha& operator +(const Fecha& f,int n){

    Fecha aux(f);
    while(n>0){

        aux++;
        n--;

    }

    return (aux);

}

//Suma
Fecha& operator +(int n,const Fecha& f){

    Fecha aux(f);
    while(n>0){

        aux++;
        n--;

    }

    return (aux);

}

//Resta
Fecha& operator -(const Fecha& f,int n){

    Fecha aux(f);
    while(n>0){

        aux--;
        n--;

    }

    return (aux);

}

//Resta
Fecha& operator -(int n,const Fecha& f){

    Fecha aux(f);
    while(n>0){

        aux--;
        n--;

    }

    return (aux);

}

//Más-igual
Fecha& Fecha::operator +=(int n){

    *this = *this + n;
    return *this;

}

//Menos-igual
Fecha& Fecha::operator -=(int n){

    *this = *this - n;
    return *this;

}

// Sobrecarga de operadores. Comparadores
bool operator ==(const Fecha& fecha1, const Fecha& fecha2){

    return (fecha1.anno() == fecha2.anno()) && (fecha1.mes() == fecha2.mes()) && (fecha1.dia() == fecha2.dia());

}

bool operator !=(const Fecha& fecha1, const Fecha& fecha2){

    return !(fecha1 == fecha2);

}

bool operator <(const Fecha& fecha1, const Fecha& fecha2){

    if (fecha1.anno() < fecha2.anno()){
        return true;
    }else if ( (fecha1.anno() == fecha2.anno()) && (fecha1.mes() < fecha2.mes()) ){ 
        return true;
    }else if ( (fecha1.anno() == fecha2.anno()) && (fecha1.mes() == fecha2.mes()) && (fecha1.dia() < fecha2.dia()) ){
        return true;
    }else return false;

}

bool operator >(const Fecha& fecha1, const Fecha& fecha2){

    return (fecha2 < fecha1);

}

bool operator <=(const Fecha& fecha1, const Fecha& fecha2){

    return ((fecha1 < fecha2) || (fecha1 == fecha2));

}

bool operator >=(const Fecha& fecha1, const Fecha& fecha2){

    return ((fecha2 < fecha1) || (fecha1 == fecha2));

}


//Destructor

Fecha::~Fecha(){



}




