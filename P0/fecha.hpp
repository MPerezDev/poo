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
        
    private:
        int dia;
        int mes;
        int anno;
        void fechaSistema(); //fechaSistema sirve para darle los valores de la fecha del sistema
                             // a los atributos de la instancia
        void comprobarFecha();
};

#endif