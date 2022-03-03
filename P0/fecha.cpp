#include <iostream>
#include <cstring>
#include <ctime>
#include "fecha.hpp"

Fecha::Fecha(int d,int m, int a): dia_{d}, mes_{m}, anno_{a}{ //Asignamos los valores

    fechaSistema(); //Comprobamos si alguno de los atributos debe ser sustituido por los de la fecha actual del sistema

}

Fecha::Fecha(Fecha& f): dia_{f.dia_}, mes_{f.mes_}, anno_{f.anno_}{} //Constructor de copia (100% mio)


void Fecha::fechaSistema(){

    std::time_t fechaSFormato = std::time(nullptr); //cogemos la fecha actual del sistema
    std::tm* fechaCFormato = std::localtime(&fechaSFormato); //Transformamos la fecha obtenida, guardándola
                                                        //en el struct std::tm, que tiene unas cuantas variables que vamos a usar ahora
    if(dia_==0) dia_ = fechaCFormato->tm_mday; //tm_mday tiene el dia del mes en el que estamos
    if(mes_==0) mes_ = fechaCFormato->tm_mon + 1; //tm_mon cuenta los meses del 0 al 11, por lo que le sumamos 1
    if(anno_==0) anno_ = fechaCFormato->tm_year + 1900; //tm_year cuenta los años desde 1900, por eso le sumamos esta cantidad

}

Fecha Fecha::operator =(const Fecha& f){

    dia_ = f.dia_;
    mes_ = f.mes_;
    anno_ = f.anno_;

}

void Fecha::comprobarFecha(){

    static const int dias[] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; //Usamos un vector en el que guardamos los días que tiene cada mes (en años no bisiestos)
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







