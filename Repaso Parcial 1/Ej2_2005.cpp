#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class Diccionario{
    
    public:
        explicit Diccionario(string nom=""); //el explicit sirve para el b)
/*c)*/  inline size_t entradas() {return dic.size();}
/*d)*/  inline void introduce(string palabra,string traduccion) {dic[palabra] = traduccion;}
/*e)*/  string traduccion(string palabra);
/*f)*/  pair<string,string> operator [](size_t indice);
    private:
        map<string,string> dic;

};

//a) y b)
Diccionario::Diccionario(string nom){

    if(!nom.empty()){

        fstream fichero(nom);
        string linea;
        string palabra1,palabra2;
        //Preguntar a pedro por los cambios hechos
        while(!getline(fichero,linea)){

        palabra1 = linea.substr(0,linea.find(" ")); //No sería find -1?
        palabra2 = linea.substr(linea.find(" ")); //No sería size -1?

        dic[palabra1] = palabra2;

        }
        fichero.close();
    }

}

//c) Inline en la especificación de la clase

//d) Inline en la especificación de la clase

//e)
string Diccionario::traduccion(string palabra){

    if(dic.count(palabra)!=0){
        string aux = dic[palabra];
        return aux;
    }else{
        string aux;
        return aux;
    }

}

//f)

pair<string,string> Diccionario::operator [](size_t indice){
    
    map<string,string>::iterator it=dic.begin();
    
    if(indice < dic.size()){
        advance(it,indice);
        return pair<string,string>(it->first,it->second);
        
    }

}

