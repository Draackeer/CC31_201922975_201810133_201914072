#ifndef LISTAREPRODUCCION_H
#define LISTAREPRODUCCION_H
#include <QMainWindow>
#include <fstream>

using namespace std;

template<typename T>

class Nodo
{
public:
    T dato;
    Nodo* next;
    Nodo* ant;
    Nodo(T dato, Nodo* next = NULL, Nodo* ant = NULL) : dato(dato), next(next), ant(ant) {}

};

template <typename T>
class ListaReproduccion
{
    Nodo<T>* head = NULL;
    Nodo<T>* cancionactual = NULL;
    int len=0;

public:
    void AppendNodo(T dato) {
        len++;
        Nodo<T>* nuevo_nodo = new Nodo<T>(dato);
        if (this->head == NULL) {
            head = nuevo_nodo;
            cancionactual = head; //Los igualas para poder recorrer atrás y adenlante la playlist en ImprAnt e ImpSig
            head->ant = NULL;
            return;
        }
        auto sgt_notNull = [](Nodo<T>* nodo) {return nodo->next != NULL; };
        Nodo<T>* ultimo_nodo = this->head;
        while (sgt_notNull(ultimo_nodo))
        {
            ultimo_nodo = ultimo_nodo->next;
        }
        ultimo_nodo->next = nuevo_nodo;
        nuevo_nodo->ant = ultimo_nodo;
    }

    T ImprimirLista() {
        Nodo<T>* nodo_actual = this->head;

        QString listaCanciones = "";
        auto no_vacio = [](Nodo<T>* nodo) {

            if (nodo != NULL)
            {
                return true;
            }
            return false;
        };

        while (no_vacio(nodo_actual))
        {
            listaCanciones = listaCanciones + nodo_actual->dato + "\n";

            nodo_actual = nodo_actual->next;

        }
              return listaCanciones;

    }

    T ImprimeAct() {
        QString CancionAct = "";
        auto notNull = [](Nodo<T>* nodo) {return nodo != NULL; };
        if (notNull(cancionactual)) {
            cancionactual = cancionactual;
        }

        CancionAct = cancionactual->dato;
        return CancionAct;
        //cout << "El siguiente es: " << cancionactual->dato;
    }

    T ImprimeSig() {
        QString CancionSig = "";
        auto sgt_notNull = [](Nodo<T>* nodo) {return nodo->next != NULL; };
        if (sgt_notNull(cancionactual)) {
            cancionactual = cancionactual->next;
        }
        else cancionactual = cancionactual;

        CancionSig = cancionactual->dato;
        return CancionSig;
        //cout << "El siguiente es: " << cancionactual->dato;
    }

    T ImprimeAnt() {
        QString CancionAnt = "";
        auto ant_notNull = [](Nodo<T>* nodo) {return nodo->ant != NULL; };
        if (ant_notNull(cancionactual)) {
            cancionactual = cancionactual->ant;
        }
        else cancionactual = cancionactual;

        CancionAnt = cancionactual->dato;
        return CancionAnt;
        //cout << "El anterior es: " << cancionactual->dato;
    }

    bool NullAnt() {
        QString CancionAnt = "";

        auto ant_notNull = [](Nodo<T>* nodo) {return nodo->ant != NULL; };
        if (ant_notNull(cancionactual)) {
            return false;
        }
        else return true;
    }

    bool NullSig(){
        QString CancionAnt = "";

        auto sgt_notNull = [](Nodo<T>* nodo) {return nodo->next != NULL; };
        if (sgt_notNull(cancionactual)) {
            return false;
        }
        else return true;
    }


    inline bool TxtExiste (const std::string& name) {
        ifstream f(name.c_str());
        return f.good();
    }

    void Eliminar(T cancionEL) {

        Nodo<T>* temp = this->head;
        if (temp != NULL && temp->dato == cancionEL)
        {
            len--;
            head->ant = NULL;
            head = temp->next;
            free(temp);
            return;
        }
        Nodo<T>* prev;
        while (temp != NULL && temp->dato != cancionEL)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            //cout << "No se encontro la cancion";
            return;
        }

        prev->next = temp->next;
        temp->next->ant = prev;
        free(temp);
        len--;
    }
    void EliminarTodo(){
        len=0;
        Nodo<T>* temp = this->head;
        while(temp!=NULL){
            head->ant = NULL;
            head = temp->next;
            temp=this->head;
        }
        free(temp);
    }

    int GetLeng(){return len;}
};
#endif // LISTAREPRODUCCION_H
