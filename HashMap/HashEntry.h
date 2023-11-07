#ifndef U05_HASH_HASHMAP_HASHENTRY_H_
#define U05_HASH_HASHMAP_HASHENTRY_H_

//HashEntry = Nodo = Fila = Entrada de la tabla
/**
 * tipo de dato atómica de tabla hash.
 * Toda tabla hash tiene una clave y un valor.
 * @tparam K //de cualquier tipo de dato: string, int,etc.
 * Dependiendo esta clave, la posición del nodo en donde se
 * almacenará.
 * @tparam T //Cualquier tipo de objeto:int, lista, pila,
 * cola, otra clase propia,etc.
 */
template <class K, class T>
class HashEntry {//mapear un valor de un lugar a otro a través de alguna función, de algún método
private:

    K clave;
    T valor;

public:
    HashEntry(K c, T v) {
        clave = c;
        valor = v;
    }

    /*
     * Getters y setters
     */

    K getClave() {
        return clave;
    }

    void setClave(K c) {
        clave = c;
    }

    T getValor() {
        return valor;
    }

    void setValor(T v) {
        valor = v;
    }
};

#endif // U05_HASH_HASHMAP_HASHENTRY_H_