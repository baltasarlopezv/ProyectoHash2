#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
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
            : grupo(grupo), codigoDeBarra(codigoDeBarra), articulo(articulo),
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
    for(int i = 0; i < clave.size(); i++) {
        idx += clave[i];
    }
    idx = idx % 512;
    //cout << "Hash de la clave " << clave << ": " << idx << endl;
    return idx;
}

int main(int argc, char** argv) {
    string s, nombre;
    cout << "cantidad de argumentos: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argumento " << i << ": " << argv[i] << endl;
    }
    string filename;
    for (int i = 2; i < argc; i++) {
        filename += argv[i];
        filename += " ";
    }
    while (filename.back() == ' ') {
        filename.pop_back();
    }
    filename.find('[');
    int cantcor = 0, num = 0, dep = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '[') {
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
    pair<int, string> deposito1;
    pair<int, string> deposito2;
    pair<int, string> deposito3;
    pair<int, string> deposito4;
    pair<int, string> deposito5;
    HashMapList<string, Producto> productoMap(512, &miHashFunc);
    int i = 0;

    std::ifstream archivo("../" + filename);
    std::vector<Producto> productosvec;


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


            productoMap.put(nuevoProducto.articulo, nuevoProducto);

        }
    }
    archivo.close();

    int opcion;
    do {
        cout << "\nMENU:" << endl;
        cout << "1. Cantidad total de articulos diferentes." << endl;
        cout << "2. Cantidad total de articulos." << endl;
        cout << "3. Listado de articulos que estan en el minimo de stock." << endl;
        cout << "4. Listado de articulos que estan en el minimo de stock y por deposito." << endl;
        cout << "5. Listado de articulos que igualan o superan determinada cantidad en stock." << endl;
        cout << "6. Stock individual de cada articulo." << endl;
        cout << "7. Stock individual de cada articulo por numero de deposito." << endl;
        cout << "8. Salir." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Cantidad total de articulos diferentes: " << Cantidadtotart.contarNodos() << endl;
                break;

                for (const auto &product: productosvec) {
                    // Crea un total_articulo (totalDepositos, articulo) y lo agrega al árbol
                    total_articulo.first = product.totalDepositos;
                    total_articulo.second = product.articulo;
                    deposito1.first = product.deposito1;
                    deposito1.second = product.articulo;
                    deposito2.first = product.deposito2;
                    deposito2.second = product.articulo;
                    deposito3.first = product.deposito3;
                    deposito3.second = product.articulo;
                    deposito4.first = product.deposito4;
                    deposito4.second = product.articulo;
                    deposito5.first = product.deposito5;
                    deposito5.second = product.articulo;


                    Cantidadtotart.put(total_articulo);
                    ardeposito1.put(deposito1);
                    ardeposito2.put(deposito2);
                    ardeposito3.put(deposito3);
                    ardeposito4.put(deposito4);
                    ardeposito5.put(deposito5);


                }

                // Insertar todos los productos en el HashMapList
                for (const Producto &producto: productosvec) {
                    // Utiliza el atributo "articulo" como clave para el HashMapList
                    productoMap.put(producto.articulo, producto);
                }

                /*
                cout << Cantidadtotart.contarNodos() << endl;
                cout<<Cantidadtotart.sumarNodos()<<endl;
                cout<<Cantidadtotart.contarNodosMenoresAlValor(1)<<endl;
                cout<<ardeposito4.contarNodosMenoresAlValor(1)<<endl;
                cout<<Cantidadtotart.contarNodosMayoresAlValor(84)<<endl;
            */
                int opcion;
                do {
                    cout << "\nMENU:" << endl;
                    cout << "1. Cantidad total de articulos diferentes." << endl;
                    cout << "2. Cantidad total de articulos." << endl;
                    cout << "3. Listado de articulos que estan en el minimo de stock." << endl;
                    cout << "4. Listado de articulos que estan en el minimo de stock y por deposito." << endl;
                    cout << "5. Listado de articulos que igualan o superan determinada cantidad en stock." << endl;
                    cout << "6. Stock individual de cada articulo." << endl;
                    cout << "7. Stock individual de cada articulo por numero de deposito." << endl;
                    cout << "8. Salir." << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                        case 1:
                            cout << "Cantidad total de articulos diferentes: " << Cantidadtotart.contarNodos() << endl;
                            break;

                        case 2: {
                            int suma = Cantidadtotart.sumarNodos();
                            cout << "Suma de todos los articulos: " << suma << endl;
                            break;
                        }
                        case 3: {
                            int valor;
                            cout << "Ingrese el valor mínimo de stock: ";
                            cin >> valor;
                            int cont = Cantidadtotart.contarNodosMenoresAlValor(valor);
                            cout << "Cantidad de articulos en el minimo de stock: " << cont << endl;
                            break;
                        }
                        case 4: {
                            int deposi, min;
                            cout << "Ingrese el deposito: ";
                            cin >> deposi;
                            cout << "Ingrese el valor minimo: ";
                            cin >> min;
                            int contDeposito = 0;

                            switch (deposi) {
                                case 1:
                                    contDeposito = ardeposito1.contarNodosMenoresAlValor(min);
                                    break;
                                case 2:
                                    contDeposito = ardeposito2.contarNodosMenoresAlValor(min);
                                    break;
                                case 3:
                                    contDeposito = ardeposito3.contarNodosMenoresAlValor(min);
                                    break;
                                case 4:
                                    contDeposito = ardeposito4.contarNodosMenoresAlValor(min);
                                    break;
                                case 5:
                                    contDeposito = ardeposito5.contarNodosMenoresAlValor(min);
                                    break;
                            }

                            cout << "Cantidad de articulos en el minimo de stock para el deposito " << deposi << ": "
                                 << contDeposito << endl;
                            break;
                        }

                        case 5: {
                            int cantidadMinima;
                            cout << "Ingrese la cantidad de stock: ";
                            cin >> cantidadMinima;
                            int conmayores = Cantidadtotart.contarNodosMayoresAlValor(cantidadMinima);
                            cout << "Cantidad de articulos que igualan o superan la cantidad ingresada: " << conmayores
                                 << endl;
                            break;
                        }

                        case 6: {
                            string articuloABuscar;
                            cin.ignore(); // Limpia el búfer antes de getline
                            cout << "Ingrese el articulo a buscar: ";
                            getline(cin, articuloABuscar);
                            productoMap.getList(articuloABuscar);
                            break;
                        }

                        case 7: {
                            string articuloABuscar;
                            cin.ignore(); // Limpia el búfer antes de getline
                            cout << "Ingrese el articulo a buscar: ";
                            getline(cin, articuloABuscar);

                            // Aquí, puedes solicitar al usuario que ingrese el número de depósito a imprimir
                            int numeroDeposito;
                            cout << "Ingrese el numero del deposito a imprimir (1-5): ";
                            cin >> numeroDeposito;

                            // Verifica si el número de depósito ingresado es válido (de 1 a 5)
                            if (numeroDeposito >= 1 && numeroDeposito <= 5) {
                                // Obtén el producto del HashMapList
                                Producto productoEncontrado = productoMap.get(articuloABuscar);

                                // Imprime el atributo del depósito específico
                                switch (numeroDeposito) {
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
                            break;
                        }

                        case 8: {
                            cout << "Saliendo del programa. Hasta luego!" << endl;
                            break;
                        }

                        default:
                            cout << "Opcion invalida. Intente nuevamente." << endl;
                    }
                } while (opcion != 8);

                return 0;
        }

/*
        if (opcion == 1) {
            cout << "Cantidad total de articulos diferentes: " << Cantidadtotart.contarNodos() << endl;
        } else if (opcion == 2) {
            int suma = Cantidadtotart.sumarNodos();
            cout << "Suma de todos los articulos: " << suma << endl;
        } else if (opcion == 3) {
            int valor;
            cout << "Ingrese el valor minimo de stock: ";
            cin >> valor;
            int cont = Cantidadtotart.contarNodosMenoresAlValor(valor);
            cout << "Cantidad de articulos en el minimo de stock: " << cont << endl;
        } else if (opcion == 4) {
            int deposi, min;
            cout << "Ingrese el deposito: ";
            cin >> deposi;
            cout << "Ingrese el valor minimo: ";
            cin >> min;
            int contDeposito = 0;

            if (deposi == 1) {
                contDeposito = ardeposito1.contarNodosMenoresAlValor(min);
            } else if (deposi == 2) {
                contDeposito = ardeposito2.contarNodosMenoresAlValor(min);
            } else if (deposi == 3) {
                contDeposito = ardeposito3.contarNodosMenoresAlValor(min);
            } else if (deposi == 4) {
                contDeposito = ardeposito4.contarNodosMenoresAlValor(min);
            } else if (deposi == 5) {
                contDeposito = ardeposito5.contarNodosMenoresAlValor(min);
            }

            cout << "Cantidad de articulos en el mínimo de stock para el deposito " << deposi << ": " << contDeposito << endl;
        } else if (opcion == 5) {
            int cantidadMinima;
            cout << "Ingrese la cantidad de stock: ";
            cin >> cantidadMinima;
            int conmayores = Cantidadtotart.contarNodosMayoresAlValor(cantidadMinima);
            cout << "Cantidad de articulos que igualan o superan la cantidad ingresada: " << conmayores << endl;
        } else if (opcion == 6) {
                string articuloABuscar;
                cin.ignore(); // Limpia el búfer antes de getline
                cout << "Ingrese el articulo a buscar: ";
                getline(cin, articuloABuscar);
                productoMap.getList(articuloABuscar);
        }else if (opcion == 7) {
                string articuloABuscar;
                cin.ignore(); // Limpia el búfer antes de getline
                cout << "Ingrese el articulo a buscar: ";
                getline(cin, articuloABuscar);

                // Aquí, puedes solicitar al usuario que ingrese el número de depósito a imprimir
                int numeroDeposito;
                cout << "Ingrese el nimero del deposito a imprimir (1-5): ";
                cin >> numeroDeposito;

                // Verifica si el número de depósito ingresado es válido (de 1 a 5)
                if (numeroDeposito >= 1 && numeroDeposito <= 5) {
                    // Obtén el producto del HashMapList
                    Producto productoEncontrado = productoMap.get(articuloABuscar);

                    // Imprime el atributo del depósito específico
                    switch (numeroDeposito) {
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
        } else if (opcion == 8) {
            cout << "Saliendo del programa. ¡Hasta luego!" << endl;
        } else {
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }
*/
    } while (opcion != 8);

    return 0;
}
