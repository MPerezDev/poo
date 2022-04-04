typedef enum {A,C,G,T} Nucleotido;



//a)

ADN::ADN(): c(nullptr), n(0){}

//b)
ADN::ADN(Nucleotido* c,size_t n): c(new Nucleotido[n]), n(n){

    for(int i=0; i<n; i++){
        this->c[i] = c[i];
    }


}

//c)
ADN::ADN(char* cadena): c(new char [strlen(cadena)]), n(strlen(cadena)){

    for(int i=0; i<=n; i++){

        if(cadena[i]='A'){
            c[i] = A;
        }else if(cadena[i]='C'){
            c[i] = C;
        }else if(cadena[i]='G'){
            c[i] = G;
        }else if(cadena[i]='T'){
            c[i] = T;
        }
    }

}

//d)

/* Sí es necesario porque, al trabajar con atributos declarados dinámicamente,
el compilador "no sabe trabajar bien". En lugar de copiar el contenido, el compilador copiaría
la dirección en lugar del contenido, por lo que si se borrase o se modificase el dato,
produciría cambios también en el objeto ADN inicializado en el constructor.
*/

//e)

Nucleotido& operator +(ADN& a, ADN& b){

    Nucleotido* cad = new Nucleotido[a.n + b.n];
    ADN aux(cad,a.n + b.n);
    memcpy(cad.c,a.c,a.n * sizeof(Nucleotido)); //por qué pone el pibe a.n*sizeof(nucleotido)
    memcpy(cad.c + a.n,b.c,sizeof(Nucleotido));
    return aux;


}


