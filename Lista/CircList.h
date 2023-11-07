#ifndef U02_LISTAS_LISTA_CIRCLIST_H_
#define U02_LISTAS_LISTA_CIRCLIST_H_
#include "./nodo.h"

template <class T>
class CircList
{
private:
    Nodo<T> *inicio;

public:
    CircList();

    CircList(const CircList<T> &li);

    ~CircList();

    bool esVacia();

    int getTamanio();

    void insertar(int pos, T dato);

    void insertarPrimero(T dato);

    void insertarUltimo(T dato);

    T getDato(int pos);

    void imprimir();
};

/**
 * Constructor de la clase CircList
 * @tparam T
 */
template <class T>
CircList<T>::CircList() { inicio = nullptr; }

/**
 * Constructor por copia de la clase CircList
 * @tparam T
 * @param li
 */
template <class T>
CircList<T>::CircList(const CircList<T> &li) { inicio = li.inicio; }

/**
 * Destructor de la clase CircList, se encarga de liberar la memoria de todos los
 * nodos utilizados en la Circlist
 * @tparam T
 */
template <class T>
CircList<T>::~CircList() {}

template <class T>
bool CircList<T>::esVacia()
{
    return inicio == nullptr;
}

template <class T>
int CircList<T>::getTamanio()
{
    Nodo<T> *aux = inicio;
    int tam = 0;

    if (esVacia())
    {
        return tam;
    }

    while (aux->getSiguiente() != inicio)
    {
        aux = aux->getSiguiente();
        tam++;
    }

    tam++;
    return tam;
}

template <class T>
void CircList<T>::insertar(int pos, T dato)
{

    if (pos != 0 && esVacia())
    {
        throw 400;
    }

    Nodo<T> *nuevo = new Nodo<T>();
    nuevo->setDato(dato);
    Nodo<T> *aux = inicio;
    int posActual = 0;

    if (pos == 0)
    {

        if (esVacia())
        {
            nuevo->setSiguiente(nuevo);
        }
        else
        {

            while (aux->getSiguiente() != inicio)
            {
                aux = aux->getSiguiente();
            }

            nuevo->setSiguiente(inicio);
            aux->setSiguiente(nuevo);
        }

        inicio = nuevo;
        return;
    }

    while (aux->getSiguiente() != inicio && posActual < pos - 1)
    {
        aux = aux->getSiguiente();
        posActual++;
    }

    if (aux->getSiguiente() == inicio && posActual < pos - 1)
    {
        throw 404;
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

template <class T>
void CircList<T>::insertarPrimero(T dato)
{
    insertar(0, dato);
}

template <class T>
void CircList<T>::insertarUltimo(T dato)
{
    Nodo<T> *aux = inicio, *nuevo;
    nuevo = new Nodo<T>;
    nuevo->setDato(dato);

    if (esVacia())
    {
        nuevo->setSiguiente(nuevo);
        inicio = nuevo;
        return;
    }

    while (aux->getSiguiente() != inicio)
    {
        aux = aux->getSiguiente();
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

template <class T>
T CircList<T>::getDato(int pos)
{
    Nodo<T> *aux = inicio;
    int posActual = 0;

    while (aux->getSiguiente() != inicio && posActual < pos)
    {
        aux = aux->getSiguiente();
        posActual++;
    }

    if (aux->getSiguiente() == inicio)
    {
        throw 404;
    }

    return aux->getDato();
}

template <class T>
void CircList<T>::imprimir()
{
    Nodo<T> *aux = inicio;

    while (aux->getSiguiente() != inicio)
    {
    std:
        std::cout << aux->getDato() << "->";
        aux = aux->getSiguiente();
    }

    std::cout << aux->getDato() << "->" << aux->getSiguiente()->getDato() << "..." << std::endl;
}

#endif // U02_LISTAS_LISTA_CIRCLIST_H_
