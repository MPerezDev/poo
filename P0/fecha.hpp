#ifndef FECHA_H_
#define FECHA_H_

class Fecha {
    public:
       explicit Fecha(int d=0,int m=0,int a=0);
       Fecha(const Fecha& f);
       Fecha(const char* cadena);
       Fecha& operator =(const Fecha& f);
       friend std::ostream& operator <<(std::ostream& os, Fecha& f);

        static const int AnnoMax = 2037; //Año limite
        static const int AnnoMin = 1902;
        class Invalida{ //Creamos una clase para las excepciones.
            public:
                Invalida(const char* m): motivo{m} {}
                const char* por_que() const noexcept {return motivo;} //¿Por qué se utiliza el noexcept?
            private:
                const char* motivo; 

        };
        int dia() const noexcept {return dia_;}
        int mes() const noexcept {return mes_;}
        int anno() const noexcept {return anno_;}

        Fecha& operator ++();
        Fecha operator ++(int);
        Fecha& operator --();
        Fecha operator --(int);
        Fecha& operator +=(int n);
        Fecha& operator -=(int n);
        
        ~Fecha();

    private:
        int dia_;
        int mes_;
        int anno_;
        void fechaSistema(); //fechaSistema sirve para darle los valores de la fecha del sistema
                             // a los atributos de la instancia
        void comprobarFecha();
        const int dias [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; //Usamos un vector en el que guardamos los días que tiene cada mes (en años no bisiestos)

};

//A continuación introducimos las sobrecargas de operadores
//Las hacemos fuera de la clase, por lo que en ellas recurrimos a
//los observadores. Se declaran en la cabecera las dos fechas con const ya que no se van a modificar.
bool operator ==(const Fecha& fecha1, const Fecha& fecha2);
bool operator !=(const Fecha& fecha1, const Fecha& fecha2);
bool operator <(const Fecha& fecha1, const Fecha& fecha2);
bool operator >(const Fecha& fecha1, const Fecha& fecha2);
bool operator <=(const Fecha& fecha1, const Fecha& fecha2);
bool operator >=(const Fecha& fecha1, const Fecha& fecha2);

//Declaramos estos operadores fuera de la clase dado que podemos encontrarnos 
//el caso de que sea entero + fecha o fecha + entero. Para el segundo nos valdría 
//con el implícito pero para el primero no, por lo que declaramos ambos operadores fuera.
//Se aplica igual para la suma.
Fecha& operator +(const Fecha& f,int n);
Fecha& operator +(int n,const Fecha& f);
Fecha& operator -(const Fecha& f,int n);
Fecha& operator -(int n,const Fecha& f);


#endif