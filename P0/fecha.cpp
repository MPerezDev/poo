#include <iostream>
#include <cstring>
#include <ctime>
#include "fecha.hpp"

Fecha::Fecha(int d,int m, int a): dia{d}, mes{m}, anno{a}{ //Asignamos los valores

    fechaSistema(); //Comprobamos si alguno de los atributos debe ser sustituido por los de la fecha actual del sistema

}

Fecha::Fecha(Fecha& f): dia{f.dia}, mes{f.mes}, anno{f.anno}{} //Constructor de copia (100% mio)


void Fecha::fechaSistema(){

    std::time_t fechaSFormato = std::time(nullptr); //cogemos la fecha actual del sistema
    std::tm* fechaCFormato = std::localtime(&fechaSFormato); //Transformamos la fecha obtenida, guardándola
                                                        //en el struct std::tm, que tiene unas cuantas variables que vamos a usar ahora
    if(dia==0) dia = fechaCFormato->tm_mday; //tm_mday tiene el dia del mes en el que estamos
    if(mes==0) mes = fechaCFormato->tm_mon + 1; //tm_mon cuenta los meses del 0 al 11
    if(anno==0) anno = fechaCFormato->tm_year + 1900; //tm_year cuenta los años desde 1900, por eso le sumamos esta cantidad

}

Fecha Fecha::operator =(const Fecha& f){

    dia = f.dia;
    mes = f.mes;
    anno = f.anno;

}

void Fecha::comprobarFecha(){

    

}




