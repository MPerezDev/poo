typedef enum {A,C,G,T} Nucleotido;

ADN::ADN(): c(nullptr), n(0){}

ADN::ADN(Nucleotido* c,size_t n): c(new char [n+1]), n(n){

    for(int i=0; i<=n; i++){
        this->c[i] = c[i];
    }


}

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

