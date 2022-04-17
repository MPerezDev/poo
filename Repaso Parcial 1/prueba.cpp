class C{
    public:
        C(int x): x(x) {}
        C operator +(const C& y);


    private:
        int x;


};

C C::operator +(const C& y){
    x=y.x;
    return *this;
}

int main(){

    int x=3;
    C c(x);
    C d(x + c);


}