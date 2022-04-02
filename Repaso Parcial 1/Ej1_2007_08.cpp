//a) Escriba los constructores y el destructor de arbol

template <typename T>
arbol<T>::arbol(): a(nullptr){}


template <typename T>
arbol<T>::arbol(const T& r): a(new arbolPropio<T>(r)){}

template <typename T>
arbol<T>::arbol(const T& r, const arbol& sai, const arbol& sad): a(new arbolPropio<T>(r,sai,sad)){}


//Destructor
template <typename T>
arbol<T>::~arbol(){

    delete a;

}

//Constructor de copia, hace falta porque el constructor de copia por defecto no trabaja bien con los
//atributos dinámicos

template <typename T>
arbol<T>::arbol(const arbol& arbol){
    if(arbol.a != nullptr){
        a = new arbolPropio<T>(arbol.(*a).r,arbol.(*a).sai,arbol.(*a).sad);
    }else{
        a = nullptr;
    }
}




