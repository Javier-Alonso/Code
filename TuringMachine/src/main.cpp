#include <fstream>
#include <iostream>
#include <string>

#include "TuringMachine.h"

using namespace std;

ostream& clearConsole();
void menu(ifstream& is1, ifstream& is2);


int main (int argc, char* argv[])
{
    if(argc != 3)
    {
        clearConsole();
        cerr << "¡Error! 2 argumentos esperados, " << argc - 1 << " proporcionados." << endl;
        return 1;
    }

    ifstream is1(argv[1]);       //maquina de turing
    ifstream is2(argv[2]);      //cinta

    if(is1.good() && is2.good())
    {
        menu(is1, is2);
    }

    else
    {
        clearConsole();
        cerr << "¡Error! No se puede abrir el archivo" << endl;
        return 1;
    }

    return 0;
}

ostream& clearConsole()
{
    return cout << "\x1b[2J\x1b[H";
}

void menu(ifstream& is1, ifstream& is2)
{
    bool flag = false;
    std::string temp;
    unsigned int opcion;

    CyA::TuringMachine TM;
    CyA::tape_t cinta;

    is1 >> TM;
    is2 >> cinta;

    clearConsole();

    do
    {
        cin.clear();
        cout << "\nSimulacion de una Maquina de Turing" << endl;
        cout << "\t1. Mostrar maquina" << endl;
        cout << "\t2. Analizar cinta" << endl;
        cout << "\t3. Reiniciar simulacion" << endl;
        cout << "\t4. Salir" << endl;
        cout << "\n>>> Introduzca una opcion: ";
        cin >> opcion;
        cin.ignore();
        clearConsole();

        switch (opcion)
        {
            case 1 :
                cout << TM;
                break;

            case 2 :
                TM.analizar_cinta(cinta);
                break;

            case 3 :
                cout << "Introduce el fichero de la TM: ";
                cin >> temp;
                is1 = ifstream(temp);

                cout << "Introduce el fichero de la cinta: ";
                cin >> temp;
                is2 = ifstream(temp);

                if(is1.good() && is2.good())
                {
                    is1 >> TM;
                    is2 >> cinta;
                }
                else
                {
                    cerr << "Error en la apertura de ficheros. La simulacion no ha sido actualizada." << endl;
                }
                break;

            case 4 :
                flag = true;
                cout << "Cerrando simulacion..." << endl;
                break;

            default :
                cout << "Opcion incorrecta" << endl;
                cin.clear();
                break;
        }
    }
    while (!flag);
}

