#include "TuringMachine.h"

namespace CyA
{

std::ifstream& TuringMachine::read(std::ifstream& is)
{
    if(is.good())
    {
        char r, w, mov;
        unsigned int arranque, id, destino;
        size_t nestados, nuplas;
        std::string linea;

        is >> (size_t &) nestados;
        is >> (unsigned int &) arranque;

        arranque_ = arranque;

        for(size_t i = 0; i < nestados; i++)
        {
            Q_.emplace(arranque++);
        }

        is.seekg(4, std::ifstream::beg);
        std::getline(is, linea);
        std::istringstream iss (linea);
        while(iss >> (unsigned int &) id)
        {
            F_.emplace(id);
        }

        is >> (size_t &) nuplas;

        for(size_t i = 0; i < nuplas; i++)
        {
            is >> (unsigned int &) id >> (char &) r >> (char &) w >> (char &) mov >> (unsigned int &) destino;
            tuplas_.emplace_back(id, r, w, mov, destino);
        }

        is.close();
        std::cout << "Maquina de Turing leida correctamente" << std::endl;
    }
    else
    {
        std::cerr << "Error en la apertura de la maquina" << std::endl;
    }

    return is;
}

std::ostream& TuringMachine::write(std::ostream& os) const
{
    os << Q_.size() << std::endl;

    os << arranque_ << std::endl;

    for(const auto& estado: F_)
    {
        os << estado << " ";
    }

    os << std::endl << tuplas_.size() << std::endl;

    for(const auto& tupla: tuplas_)
    {
        os << tupla << std::endl;
    }

    return os;
}

void TuringMachine::analizar_cinta(tape_t cinta) const
{
    bool aceptada = false;
    bool terminado = false;
    tuple_t tupla_actual{};
    unsigned int estado_actual = arranque_;

    size_t iteracion = 0;

    while(!terminado)
    {
        mostrar_transicion(cinta, estado_actual);

        if(transicion_definida(estado_actual, cinta.get_simbolo(), tupla_actual))
        {
            transitar(cinta, tupla_actual, estado_actual);
        }
        else
        {
            terminado = true;
        }
        if(iteracion++ > MAX_IT)
        {
            break;
        }
    }

    if(es_aceptacion(estado_actual) && terminado)
    {
        aceptada = true;
    }

    std::cout << "Cadena de entrada" << ((aceptada)? " " : " NO ") << "ACEPTADA" << std::endl;
}

bool TuringMachine::transicion_definida(unsigned int estado, char simbolo, tuple_t& tupla_actual) const
{
    bool existe = false;

    for(const auto& tupla: tuplas_)
    {
        if(tupla.get_id() == estado && tupla.get_lectura() == simbolo)
        {
            existe = true;
            tupla_actual = tupla;
            break;
        }
    }

    return existe;
}

bool TuringMachine::es_aceptacion(unsigned int estado_actual) const
{
    return F_.count(estado_actual) == 1;
}

void TuringMachine::transitar(tape_t& cinta, const tuple_t& tupla, unsigned int& estado) const
{
    estado = tupla.get_destino();
    cinta.escribir_simbolo(tupla.get_escritura());
    cinta.desplazar(tupla.get_movimiento());
}

void TuringMachine::mostrar_transicion(const tape_t& cinta, unsigned int estado_actual) const
{
    cinta.write_lhs(std::cout);

    std::cout << std::setw(4) << "q" << estado_actual << std::setw(4);

    cinta.write_rhs(std::cout);

    std::cout << std::endl;
}


std::ostream& operator<<(std::ostream& os, const TuringMachine& rhs)
{
    rhs.write(os);

    return os;
}

std::ifstream& operator>>(std::ifstream& is, TuringMachine& rhs)
{
    rhs.read(is);

    return is;
}


}
