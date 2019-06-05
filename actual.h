using namespace std;
class actual{
    private:
    int estadoActual;
    stack<char> pila;
    char eliminaPila;

    public:
    actual(int estado, char eliminaP);
    actual(char c, int e, char eliminaP);
    actual(char c, char eliminaP);
    actual(int estado, stack<char> p, char eliminaP);
    ~actual();
    int getEstadoActual();
    stack<char> getPila();
    void setEstadoActual(int estado);
    void setPila(stack <char> p);
    void modificar(int estado, char c);
};

actual::actual(int estado, char eliminaP){
    estadoActual=estado;
    eliminaPila=eliminaP;
}
actual::actual(char c, int estado, char eliminaP){
    pila.push(c);
    estadoActual=estado;
    eliminaPila=eliminaP;
}
actual::actual(char c, char eliminaP){
    estadoActual=0;
    pila.push(c);
    eliminaPila=eliminaP;
}
actual::actual(int estado, stack<char> p, char eliminaP){
    estadoActual=estado;
    pila=p;
    eliminaPila=eliminaP;
}
actual::~actual(){}

int actual::getEstadoActual(){
    return estadoActual;    
}
stack<char> actual::getPila(){
    return pila;
}
void actual::setEstadoActual(int estado){
    estadoActual=estado;
}
void actual::setPila(stack<char> p){
    pila=p;
}
void actual::modificar(int estado, char c){
    if (c!=eliminaPila){
        pila.push(c);
    }
    else 
        pila.pop();
    estadoActual=estado;
}

