#include <iostream>
#include <cstring>
using namespace std;
    class Libro{
    char *titulo_;
    int paginas_;
public:
    Libro() : titulo_ (new char[1]), paginas_ (0) { *titulo_ = 0; }
    Libro(const char* t, int p) : paginas_ (p){
    titulo_ = new char[strlen(t) + 1];
    strcpy(titulo_, t);
    }
    ~Libro() { delete [] titulo_; }
    void paginas(int p) { paginas_ = p; }
    int paginas() const { return paginas_; }
    const char* titulo() const { return titulo_; }
};

void mostrar(Libro l){ 
    cout << l.titulo() << " tiene " << l.paginas() << " páginas" << endl;
}

int main(){
Libro l1("Fundamentos de C++", 474), l2("Por Fin: C ISO", 224), l3;
mostrar(l3);
l3 = l1; //Se ejecuta pero no correctamente, dado que copiaría la dirección de memoria en lugar de los contenidos.
mostrar(l1), mostrar(l2), mostrar(l3);
}
