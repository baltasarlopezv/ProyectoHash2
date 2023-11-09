#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Arbol/ArbolBinarioAVL.h"
#include "HashMap/HashMapList.h"

using namespace std;



// Definición de la estructura Producto
struct Producto {
    string grupo;
    string codigoDeBarra;
    string articulo;
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
    Producto(string grupo, string codigoDeBarra, string articulo,
             int deposito1, int deposito2, int deposito3, int deposito4, int deposito5)
            : grupo(std::move(grupo)), codigoDeBarra(std::move(codigoDeBarra)), articulo(std::move(articulo)),
              deposito1(deposito1), deposito2(deposito2), deposito3(deposito3),
              deposito4(deposito4), deposito5(deposito5) {
        totalDepositos = deposito1 + deposito2 + deposito3 + deposito4 + deposito5;
    }

    friend ostream &operator<<(ostream &os, const Producto &produc) {
        os << ". Codigo de Barra: " << produc.codigoDeBarra << endl << ". Articlo: " << produc.articulo << endl
           << ". Deposito 1: " << produc.deposito1 << endl << ". Deposito 2: " << produc.deposito2 << endl << ". Deposito 3: " << produc.deposito3 << endl << ". Deposito 4: " << produc.deposito4 << endl << ". Deposito 5: " << produc.deposito5 << endl << ". Total depositos: " << produc.totalDepositos << endl;
        return os;
    }
};

unsigned int miHashFunc(string clave) {
    unsigned int idx = 0;
    for(char i : clave) {
        idx += i;
    }
    idx = idx % 512;
    //cout << "Hash de la clave " << clave << ": " << idx << endl;
    return idx;
}

int main(int argc, char** argv) {
    clock_t begin;

    string  nombre;
    cout << "cantidad de argumentos: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argumento " << i << ": " << argv[i] << endl;
    }
    string filename;
    for (int i = 2; i < argc; i++) {
        filename += argv[i];
        filename += " ";
    }
    while(filename.back() == ' ') {
        filename.pop_back();
    }
    filename.shrink_to_fit();

    int cantcor = 0, num = 0, dep = 0;

    string s = argv[1];
    s.shrink_to_fit();

    for (char i : s) {
        if (i == '[') {
            cantcor++;
        }
    }

    if (cantcor == 2) {
        try {
            //numero
            num = std::stoi(s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1));
            s.erase(s.find('['), s.find(']') - s.find('[') + 2);

        } catch (std::invalid_argument &e) {

            //nombre de producto
            nombre = s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1);
            s.erase(s.find('['), s.find(']') - s.find('[') + 2);
        }

        //deposito
        dep = std::stoi(s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1));
        s.erase(s.find('['), s.find(']') - s.find('[') + 1);

    } else if (cantcor == 1) {
        try {
            //numero
            num = std::stoi(s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1));
            s.erase(s.find('['), s.find(']') - s.find('[') + 1);

        } catch (std::invalid_argument &e) {
            //nombre de producto
            nombre = s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1);
            s.erase(s.find('['), s.find(']') - s.find('[') + 2);
        }
    }
    s.shrink_to_fit();

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
    HashMapList <string, Producto> productoMap(512, &miHashFunc);


    std::ifstream archivo("../Inventariado Fisico.csv");
    std::vector<Producto> productosvec;

    int i = 0;
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

            productoMap.put(nuevoProducto.articulo, nuevoProducto);

        }
    }
    archivo.close();

    //funciones
    begin = clock();

    if (s == "total_art_dif"){
        cout << "Cantidad total de articulos diferentes: " << Cantidadtotart.contarNodos() << endl;
    }
    if (s == "total_art") {
        int suma = Cantidadtotart.sumarNodos();
        cout << "Suma de todos los articulos: " << suma << endl;
    }
    if (s == "min_stock" && cantcor == 1) {
        cout << "Cantidad de articulos en el minimo de stock: " << Cantidadtotart.contarNodosMenoresAlValor(num) << endl;
    } else if (s == "min_stock" && cantcor == 2) {
        int contDeposito = 0;

        switch (dep) {
            case 1:
                contDeposito = ardeposito1.contarNodosMenoresAlValor(num);
                break;
            case 2:
                contDeposito = ardeposito2.contarNodosMenoresAlValor(num);
                break;
            case 3:
                contDeposito = ardeposito3.contarNodosMenoresAlValor(num);
                break;
            case 4:
                contDeposito = ardeposito4.contarNodosMenoresAlValor(num);
                break;
            case 5:
                contDeposito = ardeposito5.contarNodosMenoresAlValor(num);
                break;
        }

        cout << "Cantidad de articulos en el minimo de stock para el deposito " << dep << ": "
             << contDeposito << endl;
    }


    if (s == "stock" && cantcor == 1) {
        productoMap.getList(nombre);
    }else if (s == "stock" && cantcor == 2) {
        // Verifica si el número de depósito ingresado es válido (de 1 a 5)
        if (dep >= 1 && dep <= 5) {
            // Obtén el producto del HashMapList
            Producto productoEncontrado = productoMap.get(nombre);

            // Imprime el atributo del depósito específico
            switch (dep) {
                case 1:
                    cout << "Deposito 1: " << productoEncontrado.deposito1 << endl;
                    break;
                case 2:
                    cout << "Deposito 2: " << productoEncontrado.deposito2 << endl;
                    break;
                case 3:
                    cout << "Deposito 3: " << productoEncontrado.deposito3 << endl;
                    break;
                case 4:
                    cout << "Deposito 4: " << productoEncontrado.deposito4 << endl;
                    break;
                case 5:
                    cout << "Deposito 5: " << productoEncontrado.deposito5 << endl;
                    break;
                default:
                    cout << "Numero de deposito no valido." << endl;
            }
        } else {
            cout << "Numero de deposito no valido." << endl;
        }
    }
    if (s == "max_stock") {
        cout << "Cantidad de articulos que igualan o superan la cantidad ingresada: " << Cantidadtotart.contarNodosMayoresAlValor(num) << endl;
    }
    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Tardo " << elapsed_secs << " segundos\n" << std::endl;

    return 0;
}
