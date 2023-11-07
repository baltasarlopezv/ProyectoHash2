#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "HashMap/HashMapList.h"
#include "Arbol/ArbolBinarioAVL.h"

using namespace std;

// Define una estructura para contener los datos de Producto
struct Producto {
    std::string grupo;
    std::string codigoDeBarra;
    std::string articulo;
    int deposito1;
    int deposito2;
    int deposito3;
    int deposito4;
    int deposito5;
    int totalDepositos;

    // Constructor por defecto para inicializar los atributos
    Producto() : grupo(""), codigoDeBarra(""), articulo(""), deposito1(0), deposito2(0),
                 deposito3(0), deposito4(0), deposito5(0), totalDepositos(0) {}

    // Constructor para inicializar los atributos del objeto Producto y calcular la suma de los depósitos
    Producto(std::string grupo, std::string codigoDeBarra, std::string articulo,
             int deposito1, int deposito2, int deposito3, int deposito4, int deposito5)
            : grupo(grupo), codigoDeBarra(codigoDeBarra), articulo(articulo),
              deposito1(deposito1), deposito2(deposito2), deposito3(deposito3),
              deposito4(deposito4), deposito5(deposito5) {
        totalDepositos = deposito1 + deposito2 + deposito3 + deposito4 + deposito5;
    }
};

// Función para crear un código único para un producto
// Función para crear un código único para un producto
unsigned int miHashFunc(const std::string& clave) {
    unsigned int idx = 0;
    const int prime = 31; // Número primo para dispersión adicional

    // Suma los valores de los caracteres de la cadena
    for (char c : clave) {
        idx = (idx * prime + c) % 500;
    }

    std::cout << "Hash de la clave " << clave << ": " << idx << std::endl;
    return idx;
}


int main() {
    ArbolBinarioAVL<pair<int, string >> Cantidadtotart;
    ArbolBinarioAVL<pair<int, string >> ardeposito1;
    ArbolBinarioAVL<pair<int, string >> ardeposito2;
    ArbolBinarioAVL<pair<int, string >> ardeposito3;
    ArbolBinarioAVL<pair<int, string >> ardeposito4;
    ArbolBinarioAVL<pair<int, string >> ardeposito5;
    pair<int, string> total_articulo;
    pair<int, string> Deposito1;
    pair<int, string> Deposito2;
    pair<int, string> Deposito3;
    pair<int, string> Deposito4;
    pair<int, string> Deposito5;

    std::ifstream archivo("C:\\Users\\Lenovo\\Documents\\2do ano\\Programacion III\\ProyectoHash2\\Inventariado Fisico.csv");
    std::vector<Producto> productosvec;


    int i=0;
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream stream(linea);
            std::string grupo, codigoDeBarra, articulo;
            int deposito1, deposito2, deposito3, deposito4, deposito5;

            // Lee los valores de la línea separados por comas
            std::getline(stream, grupo, ',');
            std::getline(stream, codigoDeBarra, ',');
            std::getline(stream, articulo, ',');

            // Lee los depósitos y asigna cero si están vacíos
            std::string deposito1Str, deposito2Str, deposito3Str, deposito4Str, deposito5Str;
            std::getline(stream, deposito1Str, ',');
            std::getline(stream, deposito2Str, ',');
            std::getline(stream, deposito3Str, ',');
            std::getline(stream, deposito4Str, ',');
            std::getline(stream, deposito5Str, ',');

            deposito1 = deposito1Str.empty() ? 0 : std::stoi(deposito1Str);
            deposito2 = deposito2Str.empty() ? 0 : std::stoi(deposito2Str);
            deposito3 = deposito3Str.empty() ? 0 : std::stoi(deposito3Str);
            deposito4 = deposito4Str.empty() ? 0 : std::stoi(deposito4Str);
            deposito5 = deposito5Str.empty() ? 0 : std::stoi(deposito5Str);

            // Crea un objeto de la estructura Producto usando el constructor
            Producto nuevoProducto(grupo, codigoDeBarra, articulo, deposito1, deposito2, deposito3, deposito4,
                                   deposito5);


            // Agrega el objeto a la lista de productos
            productosvec.push_back(nuevoProducto);

            total_articulo.first= productosvec[i].totalDepositos;
            total_articulo.second= productosvec[i].articulo;
            Deposito1.first= productosvec[i].deposito1;
            Deposito1.second= productosvec[i].articulo;
            Deposito2.first= productosvec[i].deposito2;
            Deposito2.second= productosvec[i].articulo;
            Deposito3.first= productosvec[i].deposito3;
            Deposito3.second= productosvec[i].articulo;
            Deposito4.first= productosvec[i].deposito4;
            Deposito4.second= productosvec[i].articulo;
            Deposito5.first= productosvec[i].deposito5;
            Deposito5.second= productosvec[i].articulo;

            Cantidadtotart.put(total_articulo);
            ardeposito1.put(Deposito1);
            ardeposito2.put(Deposito2);
            ardeposito3.put(Deposito3);
            ardeposito4.put(Deposito4);
            ardeposito5.put(Deposito5);
            i++;

        }
    }

    archivo.close();

    // Crear un HashMapList para almacenar los productos utilizando la función de hash personalizada
    HashMapList<string, Producto> productos(467, &miHashFunc);

    return 0;
}
