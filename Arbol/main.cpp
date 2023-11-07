#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <stdlib.h>

#include "ArbolBinarioAVL.h"
#include "ArbolBinario.h"

using namespace std;

int main(int argc, char **argv)
{
    string archivoInput = "./arr.txt";
    bool verbose = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "**************************************" << endl;
            cout << "*       Instrucciones de Uso         *" << endl;
            cout << "*------------------------------------*" << endl;
            cout << "* -t  [opcional]: 'ordenado' usa el  *" << endl;
            cout << "*     archivo arr_ordenado.txt.      *" << endl;
            cout << "*     'inverso' utiliza el archivo   *" << endl;
            cout << "*     arr_inverso.txt. Si no se pasa *" << endl;
            cout << "*     el argumento, se usa arr.txt   *" << endl;
            cout << "* -v  [opcional]: si esta presente   *" << endl;
            cout << "*     se imprimen los arboles al     *" << endl;
            cout << "*     final de la ejecución.         *" << endl;
            cout << "*                                    *" << endl;
            cout << "* Ejemplos validos                   *" << endl;
            cout << "*   ./main -t ordenado               *" << endl;
            cout << "*   ./main -t inverso -v             *" << endl;
            cout << "*   ./main -v -t ordenado            *" << endl;
            cout << "*   ./main -v                        *" << endl;
            cout << "*   ./main                           *" << endl;
            cout << "**************************************" << endl;

            return 0;
        }
        else if (strcmp(argv[i], "-v") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (strcmp(argv[i + 1], "ordenado") == 0)
            {
                archivoInput = "./arr_ordenado.txt";
            }
            else if (strcmp(argv[i + 1], "inverso") == 0)
            {
                archivoInput = "./arr_inverso.txt";
            }
            ++i;
        }
    }
    ArbolBinario<int> arbolClasico;
    ArbolBinarioAVL<int> arbolAVL;

    fstream fin;
    string aux;
    string algoritmo;
    fin.open(archivoInput, ios::in);
    while (getline(fin, aux, ','))
    {
        int valor = stoi(aux);
        try
        {
            arbolClasico.put(valor);
            arbolAVL.put(valor);
        }
        catch (int error)
        {
        } // Valor repetido en el arbol, omitiendolo..."
    }

    clock_t inicio, final;
    double tBST, tAVL;
    srand(time(NULL));
    int buscarRandom = (rand() % 1000 + 0); //Generamos un valor aleatorio para buscar

    //Buscar un valor en arbol clasico
    //y medir cuanto tarda en encontrarlo
    inicio = clock();
    try
    {
        arbolClasico.search(buscarRandom);
    }
    catch (int error)
    {
        //cout << "Valor " << buscarRandom << " no presente en el arbol" << endl;
    }
    final = clock();
    tBST = static_cast<double>(final - inicio) / CLOCKS_PER_SEC;

    //Buscar un valor en arbol AVL (balanceado)
    //y medir cuanto tarda en encontrarlo
    inicio = clock();
    try
    {
        arbolAVL.search(buscarRandom);
    }
    catch (int error)
    {
        cout << "Valor " << buscarRandom << " no presente en el arbol" << endl;
    }
    final = clock();
    tAVL = static_cast<double>(final - inicio) / CLOCKS_PER_SEC;

    if (verbose)
    {
        cout << "********************" << endl;
        cout << "Arbol Clasico" << endl;
        cout << "********************" << endl;
        arbolClasico.print();

        cout << endl;
        cout << endl;

        cout << "********************" << endl;
        cout << "Arbol AVL" << endl;
        cout << "********************" << endl;
        arbolAVL.print();
    }

    cout << "Tiempo de busqueda p/ Arbol Clasico: " << tBST << endl;
    cout << "Tiempo de busqueda p/ Arbol AVL: " << tAVL << endl;

    return 0;
}