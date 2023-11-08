#ifndef U05_HASH_HASHMAP_HASHMAPLIST_H_
#define U05_HASH_HASHMAP_HASHMAPLIST_H_

#include "HashEntry.h"
#include "Lista.h"

//Tabla hash con manejo de colisiones usando listas enlazadas
template <class K, class T>
class HashMapList {
private:
    Lista<HashEntry<K, T>> **tabla;

    unsigned int tamanio;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);

public:
    explicit HashMapList(unsigned int k);

    HashMapList(unsigned int k, unsigned int (*hashFuncP)(K clave));

    void getList(K clave);

    void put(K clave, T valor);

    void remove(K clave);

    ~HashMapList();

    bool esVacio();

    void print();

    T get(K clave);
};

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
    for(int i = 0; i < tamanio; i++) {
        tabla[i] = NULL;
    }
    hashFuncP = hashFunc;
}

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k, unsigned int (*fp)(K)) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
    for(int i = 0; i < tamanio; i++) {
        tabla[i] = NULL;
    }
    hashFuncP = fp;
}

template <class K, class T>
HashMapList<K, T>::~HashMapList() {
    for(int i = 0; i < tamanio; i++) {
        if(tabla[i] != NULL) {
            delete tabla[i];
        }
    }
}

template <class K, class T>
void HashMapList<K, T>::put(K clave, T valor) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == NULL) {
        tabla[pos] = new Lista<HashEntry<K, T>>();
    }

    HashEntry<K, T> objetohash(clave, valor);
    tabla[pos]->insertarUltimo(objetohash);
}

template <class K, class T>
void HashMapList<K, T>::remove(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        throw 404;
    }

    T dato;// = get(clave);

    tabla[pos]->remove({clave, dato});

    if(tabla[pos]->esVacio()) {
        delete tabla[pos];
        tabla[pos] = NULL;
    }
}

template <class K, class T>
bool HashMapList<K, T>::esVacio() {
    for(int i = 0; i < tamanio; i++) {
        if(tabla[i] != NULL) {
            return false;
        }
    }
    return true;
}

template <class K, class T>
unsigned int HashMapList<K, T>::hashFunc(K clave) {
    return (unsigned int) clave;
}

template <class K, class T>
void HashMapList<K, T>::getList(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == NULL) {
        throw 404;
    }

    Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();

    while (aux != NULL) {
        if (aux->getDato().getClave() == clave) {
            std::cout << aux->getDato().getValor() << std::endl;
            return;  // Sale del bucle cuando se encuentra el producto deseado
        }
        aux = aux->getSiguiente();
    }

    // Si llega a este punto, significa que no se encontró el producto
    std::cout << "Producto no encontrado" << std::endl;
}

template <class K, class T>
T HashMapList<K, T>::get(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == NULL) {
        throw std::runtime_error("La clave no existe en el mapa.");
    }

    Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();

    while (aux != NULL) {
        if (aux->getDato().getClave() == clave) {
            return aux->getDato().getValor();
        }
        aux = aux->getSiguiente();
    }

    throw std::runtime_error("La clave no existe en el mapa.");
}


#endif // U05_HASH_HASHMAP_HASHMAPLIST_H_