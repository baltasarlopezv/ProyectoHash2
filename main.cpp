#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "HashMap/HashMapList.h"

// Define una estructura para contener los datos de Producto
struct ProductoData {
    std::string categoria;
    std::string numerocategoria;
    std::string codigo;
    std::string codigounico;
    std::string descripcion;
    int campo1;
    int campo2;
    int campo3;
    int campo4;
    int campo5;
};

std::ostream& operator<<(std::ostream& os, const ProductoData& producto) {
    os << "Categoria: " << producto.categoria << "\n";
    os << "Numero de Categoria: " << producto.numerocategoria << "\n";
    os << "Codigo: " << producto.codigo << "\n";
    os << "Codigo Unico: " << producto.codigounico << "\n";
    os << "Descripcion: " << producto.descripcion << "\n";
    os << "Campo1: " << producto.campo1 << "\n";
    os << "Campo2: " << producto.campo2 << "\n";
    os << "Campo3: " << producto.campo3 << "\n";
    os << "Campo4: " << producto.campo4 << "\n";
    os << "Campo5: " << producto.campo5 << "\n";
    return os;
}

// Función para crear un código único para un producto
std::string CrearCodigoUnico(int& contador) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << contador;
    contador++;
    return ss.str();
}

int main() {
    std::ifstream archivo("C:\\Users\\Lenovo\\Documents\\2do ano\\Programacion III\\ProyectoProg3\\ProyectoProg3\\Inventariado Fisico.csv");

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    // Crea un HashMapList para almacenar los productos por su código de hash
    HashMapList<std::string, ProductoData> productosMap(479, &CrearCodigoUnico);

    std::string linea;
    int contador = 0;
    while (std::getline(archivo, linea)) {
        ProductoData producto;
        size_t pos = 0;

        for (int i = 0; i < 8; i++) {
            size_t next_comma = linea.find(',', pos);
            std::string campo;

            if (next_comma != std::string::npos) {
                campo = linea.substr(pos, next_comma - pos);
                pos = next_comma + 1;
            } else {
                campo = linea.substr(pos);
            }

            switch (i) {
                case 0:
                    if (!campo.empty()) {
                        producto.categoria = campo;
                    }
                    break;
                case 1:
                    producto.codigo = campo;
                    break;
                case 2:
                    producto.descripcion = campo;
                    break;
                case 3:
                    try {
                        producto.campo1 = std::stoi(campo);
                    } catch (const std::invalid_argument& e) {
                        producto.campo1 = 0;
                    }
                    break;
                case 4:
                    try {
                        producto.campo2 = std::stoi(campo);
                    } catch (const std::invalid_argument& e) {
                        producto.campo2 = 0;
                    }
                    break;
                case 5:
                    try {
                        producto.campo3 = std::stoi(campo);
                    } catch (const std::invalid_argument& e) {
                        producto.campo3 = 0;
                    }
                    break;
                case 6:
                    try {
                        producto.campo4 = std::stoi(campo);
                    } catch (const std::invalid_argument& e) {
                        producto.campo4 = 0;
                    }
                    break;
                case 7:
                    try {
                        producto.campo5 = std::stoi(campo);
                    } catch (const std::invalid_argument& e) {
                        producto.campo5 = 0;
                    }
                    break;
            }
        }

        // Después de asignar los valores a la estructura ProductoData, crea el código único
        producto.codigounico = CrearCodigoUnico(contador);

        // Genera el valor del hash
        std::string hash = producto.categoria + producto.codigounico;

        // Almacena los datos del producto en el mapa utilizando el código de hash como clave
        productosMap.put(hash, producto);
    }

    archivo.close();

    // Solicitar al usuario el código de hash del producto deseado
    std::string codigo_hash;
    std::cout << "Ingrese el código de hash del producto deseado: ";
    std::cin >> codigo_hash;

    // Imprimir los detalles del producto usando la sobrecarga del operador <<
    if (!productosMap.esVacio()) {
        std::cout << "Detalles del producto: " << std::endl;
        productosMap.getList(codigo_hash);
    } else {
        std::cout << "El mapa de productos está vacío." << std::endl;
    }

    return 0;
}
