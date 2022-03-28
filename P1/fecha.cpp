#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fecha.hpp"


//#include <locale>
//std::locale::global(std::locale("es_ES.utf8")); Para cambiar al sistema local

Fecha::Fecha(int d,int m, int a): dia_{d}, mes_{m}, anno_{a}{ //Asignamos los valores

    fechaSistema(); //Comprobamos si alguno de los atributos debe ser sustituido por los de la fecha actual del sistema
    comprobarFecha();

}

//Constructor de copia no hace falta, se coge automáticamente con el constructor por defecto
//Fecha::Fecha(const Fecha& f): dia_(f.dia_), mes_(f.mes_), anno_(f.anno_){}


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
/*Fecha& Fecha::operator =(const Fecha& f){

    dia_ = f.dia_;
    mes_ = f.mes_;
    anno_ = f.anno_;

    return *this;

}*/

//Con este método comprobamos que la fecha esté dentro de los valores correctos
void Fecha::comprobarFecha(){


    static int dias[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
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
    
    if(anno_ < AnnoMinimo || anno_ > AnnoMaximo){ //Comprobamos que el año introducido está dentro los valores permitidos
        throw Invalida ("Anno incorrecto");
    }

}

//Método explícito de conversión a cadena 
const char* Fecha::cadena() const{

    char dias_[7][15] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
    char meses_[12][15] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    char * cadena = new char[50];
    struct tm aux={};
    aux.tm_mday = dia_;
    aux.tm_mon = mes_ -1;
    aux.tm_year = anno_ - 1900;
    mktime(&aux);
    

    sprintf(cadena,"%s %d de %s de %d", dias_[aux.tm_wday], aux.tm_mday, meses_[aux.tm_mon],aux.tm_year+1900);

    return cadena;

}


//Sobrecarga de operador de inserción <<
std::ostream& operator <<(std::ostream& os,const Fecha& f){

    char dias_[7][15] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
    char meses_[12][15] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    char * cadena = new char[50];
    struct tm aux={};
    aux.tm_mday = f.dia();
    aux.tm_mon = f.mes() -1;
    aux.tm_year = f.anno() - 1900;
    mktime(&aux);

    return os << dias_[aux.tm_wday] << " " << aux.tm_mday << " de " << meses_[aux.tm_mon] << " de " << aux.tm_year + 1900;

}

//Sobrecarga de operador de extracción >>
std::istream& operator >>(std::istream& is,Fecha& f){

    char* cadAux = new char[11];

    is.width(11);
    is >> cadAux;
    Fecha fecAux(cadAux);
    f = fecAux;

    return is;

}

//Sobrecarga de operadores. Asignaciones

//Preincremento
Fecha& Fecha::operator ++(){

    dia_ += 1;
    struct tm aux={};
    aux.tm_mday = dia_;
    aux.tm_mon = mes_ -1;
    aux.tm_year = anno_ - 1900;
    mktime(&aux);
    
    /*dia_++;
    if(dia_ > dias[mes_]){
        dia_ = 1;
        mes_++;
        if(mes_ > 12){
            mes_ = 1;
            anno_++;
        }
    }*/

    dia_ = aux.tm_mday;
    mes_ = aux.tm_mon +1;
    anno_ = aux.tm_year + 1900;

    comprobarFecha();

    return *this;
    
}

//Postincremento
Fecha Fecha::operator ++(int){

    Fecha f = *this;
    ++(*this);
    return f;

}

//Predecremento
Fecha& Fecha::operator --(){

    /*dia_--;
    if(dia_ <= 0){
        dia_ = dias[mes_];
        mes_--;
        if(mes_ <= 0){
            mes_ = 12;
            anno_--;
        }

    }*/

    dia_ -= 1;
    struct tm aux={};
    aux.tm_mday = dia_;
    aux.tm_mon = mes_ -1;
    aux.tm_year = anno_ - 1900;
    mktime(&aux);

    dia_ = aux.tm_mday;
    mes_ = aux.tm_mon +1;
    anno_ = aux.tm_year + 1900;

    comprobarFecha();
    return *this;

}

//Postdecremento
Fecha Fecha::operator --(int){

    Fecha f = *this;
    --(*this);
    return f;

}

//Suma 1 (Fecha -- entero)
Fecha& operator +(const Fecha& f,int n){

    Fecha aux(f);
    while(n>0){

        aux++;
        n--;

    }

    return (aux);

}

//Suma 2 (entero -- Fecha)
Fecha& operator +(int n,const Fecha& f){

    Fecha aux(f);
    while(n>0){

        aux++;
        n--;

    }

    return (aux);

}

//Resta 1 (Fecha -- entero)
Fecha& operator -(const Fecha& f,int n){

    Fecha aux(f);
    while(n>0){

        aux--;
        n--;

    }

    return (aux);

}

//Resta 2 (entero -- Fecha)
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

/*Fecha::~Fecha(){



}*/




