#include <fstream>
#include <iostream>
#include <string>

#include "DFA.h"

using namespace std;

void menu();
ostream& clearConsole();

int main ()
{
    menu();

    return 0;
}

void menu()
{
    bool flag = false;
    ifstream textfile;
    ofstream salida;
    std::string fichero;
    unsigned int opcion;

    CyA::DFA automata;

    clearConsole();

    do
    {
        cin.clear();
        cout << "Automata Finito Determinista" << endl;
        cout << "\t1. Leer DFA" << endl;
        cout << "\t2. Mostrar DFA" << endl;
        cout << "\t3. Identificar estados de muerte" << endl;
        cout << "\t4. Analizar cadena" << endl;
        cout << "\t5. Minimizar DFA" << endl;
        cout << "\t6. Exportar DFA" << endl;
        cout << "\t7. Salir" << endl;
        cout << "\n>>> Introduzca una opción: ";
        cin >> opcion;
        cin.clear();

        switch (opcion)
        {

        case 1 :
            clearConsole();
            textfile >> automata;
            break;

        case 2 :
            clearConsole();
            if(automata.no_definido())
                cout << "Automata no definido." << endl;
            else
                cout << automata;
            break;

        case 3 :
            clearConsole();
            if(automata.no_definido())
                cout << "Automata no definido." << endl;
            else
                automata.estados_muerte();
            break;

        case 4 :
            clearConsole();
            if(automata.no_definido())
                cout << "Automata no definido." << endl;
            else
                automata.analizar_cadena();
            break;

        case 5 :
            clearConsole();
            if(automata.no_definido())
                cout << "Automata no definido." << endl;
            else
                automata.minimizar();
            break;

        case 6 :
            clearConsole();
            if(automata.no_definido())
                cout << "Automata no definido." << endl;
            else
            {
                cout << "Introduce el nombre del fichero: ";
                cin >> fichero;
                salida.open(fichero);
                if(salida.is_open())
                    salida << automata;
                else
                    cerr << "Error en la creacion del fichero" << endl;
            }
            break;

        case 7 :
            flag = true;
            clearConsole();
            cout << "Cerrando simulacion..." << endl;
            break;

        default :
            clearConsole();
            cout << "Opcion incorrecta" << endl;
            cin.clear();
            break;
        }
    }
    while (!flag);
}


ostream& clearConsole()
{
    return cout << "\x1b[2J\x1b[H";
}
