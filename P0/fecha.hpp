#ifndef FECHA_H_
#define FECHA_H_

class Fecha {
    public:
       explicit Fecha(int d=0,int m=0,int a=0);
       Fecha(Fecha& f);
       Fecha(const char* cadena);
       Fecha operator =(const Fecha& f);

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


    private:
        int dia_;
        int mes_;
        int anno_;
        void fechaSistema(); //fechaSistema sirve para darle los valores de la fecha del sistema
                             // a los atributos de la instancia
        void comprobarFecha();
};

//A continuación introducimos las sobrecargas de operadores
//Las hacemos fuera de la clase, por lo que en ellas recurrimos a
//los observadores
bool operator ==(const Fecha& fecha1, const Fecha& fecha2);
bool operator !=(const Fecha& fecha1, const Fecha& fecha2);
bool operator <(const Fecha& fecha1, const Fecha& fecha2);
bool operator >(const Fecha& fecha1, const Fecha& fecha2);
bool operator <=(const Fecha& fecha1, const Fecha& fecha2);
bool operator >=(const Fecha& fecha1, const Fecha& fecha2);


#endif