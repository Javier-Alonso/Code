#include <fstream>
#include <iostream>
#include <string>

#include "GR_t.h"

using namespace std;

ostream& clearConsole();

int main (int argc, char* argv[])
{
    if(argc != 3)
    {
        clearConsole();
        cerr << "¡Error! 2 argumentos esperados, " << argc - 1 << " proporcionados." << endl;
        return 1;
    }

    ifstream is(argv[1]);       //gramatica sin simplificar
    ofstream os(argv[2]);       //gramatica simplificada

    if(is.good() && os.good())
    {
        clearConsole();

        CyA::GR_t gramatica;

        is >> gramatica;

        gramatica.simplificar();

        os << gramatica;

        cout << "Gramatica simplificada correctamente" << endl;

        is.close();
        os.close();
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
