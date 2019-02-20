#include <fstream>
#include <iostream>

#include "NFA.h"

using namespace std;

void menu(void);
ostream& clearConsole(void);

int main (void)
{
    menu();

    return 0;
}

void menu(void)
{
    bool flag = false;
    ifstream textfile;
    unsigned int opcion;

    CyA::NFA automata;

    clearConsole();

    do
    {
        cin.clear();
        cout << "Automata Finito No Determinista" << endl;
        cout << "\t1. Leer NFA" << endl;
        cout << "\t2. Mostrar NFA" << endl;
        cout << "\t3. Identificar estados de muerte" << endl;
        cout << "\t4. Identificar estados importantes" << endl;
        cout << "\t5. ¿Es DFA?" << endl;
        cout << "\t6. Analizar cadena" << endl;
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
            if(!automata.definido())
                cout << "Automata no definido." << endl;
            else
                cout << automata;
            break;

        case 3 :
            clearConsole();
            if(!automata.definido())
                cout << "Automata no definido." << endl;
            else
                automata.estados_muerte();
            break;

        case 4 :
            clearConsole();
            if(!automata.definido())
                cout << "Automata no definido." << endl;
            else
                automata.estados_importantes();
            break;

        case 5 :
            clearConsole();
            if(!automata.definido())
                cout << "Automata no definido." << endl;
            else
                std::cout << "El Automata" << ((automata.es_dfa())? " " : " NO ") << "es un DFA" << std::endl;
            break;

        case 6 :
            clearConsole();
            if(!automata.definido())
                cout << "Automata no definido." << endl;
            else
                automata.leer_cadena();
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


ostream& clearConsole(void)
{
    return cout << "\x1b[2J\x1b[H";
}
