#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

void pausa () { cin.clear(); cin.sync(); cin.ignore(); }

template <class DATO>
class Cola;

class Constancia {

    private:

        string nombre;
        string carrera;
        int totalMaterias;
        float promedio;

    public:

        Constancia(){nombre = "", carrera = ""; totalMaterias = 0; promedio = 0;}
        void setNombre(string aux){nombre = aux;}
        void setCarrera(string aux){carrera = aux;}
        void setTotalMaterias(int aux){totalMaterias = aux;} 
        void setPromedio(float aux){promedio = aux;}
        string getNombre(){return nombre;}
        string getCarrera(){return carrera;}
        int getTotalMaterias(){return totalMaterias;}
        float getPromedio(){return promedio;}

        friend ostream& operator << (ostream& out, const Constancia& x){
            out << "Estudiante: " << x.nombre <<endl;
            out << "Carrera: " << x.carrera <<endl;
            out << "Total de materias: " << x.totalMaterias <<endl;
            out << "Promedio: " << x.promedio <<endl;
            return out;
        }

        Constancia &operator = (const Constancia x) {
            nombre = x.nombre;
            carrera = x.carrera;
            totalMaterias = x.totalMaterias;
            promedio = x.promedio;
            return *this;
        }

};

template <class DATO>
class Nodo {

    private:

        DATO dato;
        Nodo<DATO> *sig;

    public:

        Nodo() : sig(nullptr){}; 
        void setDato (DATO aux) {dato = aux;}
        DATO getDato ()const {return dato;}
        friend class Cola<DATO>;

};

template <class DATO>
class Cola {

    private:

        Nodo<DATO> *lista;
        Nodo<DATO> *ultimo()const;
        Nodo<DATO> *primero()const;
        Nodo<DATO> *anterior(Nodo<DATO> *pos)const;
        bool insertar(Nodo<DATO> *pos, DATO elem);
        bool eliminar(Nodo<DATO> *pos);

    public:

        Cola() : lista(nullptr){};
        bool vacia()const;
        void imprimir()const;
        bool enqueue (DATO elem);
        bool dequeue ();
        DATO frente();

};

template <class DATO>
bool Cola<DATO>::vacia()const {
    if (lista == nullptr)
        return true;
    return false;
}

template<class DATO>
void Cola<DATO>::imprimir()const{
    Nodo<DATO> *aux = lista;
    int i = 1;
    while(aux != nullptr){
        cout << i++ << ")._ " <<endl;
        cout << aux->dato <<endl<<endl;
        aux = aux->sig;
    }
}

template<class DATO>
bool Cola<DATO>::eliminar(Nodo<DATO> *pos){
    if(vacia() || pos == nullptr){
        return false;
    }
    if(pos == lista){
        lista = lista->sig;
    }
    else{
        anterior(pos)->sig = pos->sig;
    }
    delete pos;

    return true;
}

template<class DATO>
Nodo<DATO> *Cola<DATO>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}

template<class DATO>
Nodo<DATO> *Cola<DATO>::ultimo()const {
    if(vacia()){
        return nullptr;
    }
    Nodo<DATO> *aux = lista;
    while(aux -> sig != nullptr){
        aux = aux->sig;
    }
    return aux;
}

template <class DATO>
Nodo<DATO> *Cola<DATO>::anterior(Nodo<DATO> *pos)const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    Nodo<DATO> *aux = lista;
    while ((aux != nullptr) && (aux->sig != pos)) {
        aux = aux->sig;
    }
    return aux;
}

template<class DATO>
bool Cola<DATO>::insertar(Nodo<DATO> *pos, DATO elem){
    Nodo<DATO> *aux = new Nodo<DATO>;
    aux->dato = elem;
    if(pos == nullptr){
        aux->sig = lista;
        lista = aux;
        return true;
    }
    else{
        aux->sig = pos->sig;
        pos->sig = aux;
        return true;
    }
    return false;
}

template<class DATO>
bool Cola<DATO>::enqueue(DATO elem) {
    return insertar(ultimo(), elem);
    
}

template<class DATO>
bool Cola<DATO>::dequeue () {
    return eliminar(primero());
}

template<class DATO>
DATO Cola<DATO>::frente() {
    if(!vacia()){
       return primero()->dato;
    }
}

int main () {

    Cola <Constancia> estudiantes;

    short opc;

    do {

        system(CLEAR);
        cout << "***DIRECCION ESCOLAR***" <<endl<<endl;

        cout << "Que opcion quieres elegir?" <<endl<<endl;
        cout << "1) Dar de alta a un alumno." <<endl;
        cout << "2) Elaborar una constancia." <<endl;
        cout << "3) Mostrar las constancias pendientes." <<endl;
        cout << "0) Salir." <<endl<<endl;
        cout << "Tu opcion >> ";
        cin >> opc;

        switch (opc) {

            case 0: break;
            
            case 1:{

                Constancia constAlta;
                string auxNombre, auxCarrera;
                int auxInt;
                float auxFloat;

                system(CLEAR);
                cout << "***DIRECCION ESCOLAR***" <<endl;
                cout << "***ALTA DE CONSTANCIA***" <<endl<<endl;

                cout << "Nombre del alumno: ";
                fflush(stdin);
                getline(cin, auxNombre);

                cout << "Carrera que estudia: ";
                fflush(stdin);
                getline(cin, auxCarrera);

                cout << "Total de materias en el semestre: ";
                cin >> auxInt;

                cout << "Promedio del Alumno: ";
                cin >> auxFloat;

                constAlta.setNombre(auxNombre);
                constAlta.setCarrera(auxCarrera);
                constAlta.setTotalMaterias(auxInt);
                constAlta.setPromedio(auxFloat);

                bool alta = estudiantes.enqueue(constAlta);

                if (alta) {
                    cout << endl << "Registro exitoso...";
                    pausa();
                }
                else {
                    cout << endl << "Error al encolar el alta...";
                    pausa();
                }
            }break;
        
            case 2:

                if (estudiantes.vacia()){
                    system(CLEAR);    
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***CONSTANCIA DEL ALUMNO***" <<endl<<endl;

                    cout << "No hay solicitudes pendientes...";
                    pausa();
                }
                else {
                    system(CLEAR);
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***CONSTANCIA DEL ALUMNO***" <<endl<<endl;

                    Constancia constAux = estudiantes.frente();

                    cout << "Se va a emitir la siguiente constancia: " <<endl<<endl;
                    cout << "El siguiente alumno cursa actualmente en la Universidad de Guadalajara: " <<endl;
                    cout << "Nombre del interesado: " << constAux.getNombre() << "." <<endl;
                    cout << "Carrera que estudia: " << constAux.getCarrera() << "." <<endl;
                    cout << "Total de materias que cursa actualmente: " << constAux.getTotalMaterias() << "." <<endl;
                    cout << "Promedio del estudiante: " << constAux.getPromedio() << "." <<endl<<endl;

                    cout << "Al ser emitida, la solicitud sera borrada...";
                    pausa();

                    bool borrado = estudiantes.dequeue();

                    if (borrado) {
                        cout <<endl<<endl << "Soliciutd borrada...";
                        pausa();
                    }
                    else {
                        cout << "No se pudo borrar la solicitud, intentelo de nuevo...";
                        pausa();
                    }
                }

            break;

            case 3:
                
                if (estudiantes.vacia()) {
                    system(CLEAR);
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***SOLICITUDES DE CONSTANCIAS***" <<endl<<endl;
                    cout << "Error, no hay datos...";
                    pausa();
                }
                else {
                    system(CLEAR);
                    cout << "***DIRECCION ESCOLAR***" <<endl;
                    cout << "***SOLICITUDES DE CONSTANCIAS***" <<endl<<endl;
                    estudiantes.imprimir();
                    pausa();
                }

            break;
            
            default:

                cout << endl << "Opcion erronea, intentalo de nuevo";
                pausa();

            break;
        }

    } while (opc != 0);

    return 0;

}