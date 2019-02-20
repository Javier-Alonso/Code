#include "tape_t.h"

namespace CyA
{


std::ifstream& tape_t::read(std::ifstream& is)
{
    if(is.good())
    {
        std::string temp;
        std::getline(is, temp);

        cadena_.insert(cadena_.begin(), temp.cbegin(), temp.cend());

        is.close();
        std::cout << "Cinta leida correctamente" << std::endl;
    }
    else
    {
        std::cerr << "Error en la apertura de la cinta" << std::endl;
    }

    return is;
}

std::ostream& tape_t::write_rhs(std::ostream& os) const
{
    for(size_t i = posicion_; i < cadena_.size(); i++)
    {
        os << cadena_.at(i);
    }

    if(cadena_.back() != simbolo_blanco)
    {
        os << simbolo_blanco;
    }

    return os;
}

std::ostream& tape_t::write_lhs(std::ostream& os) const
{
    os << simbolo_blanco;

    for(size_t i = 0; i < posicion_; i++)
    {
        os << cadena_.at(i);
    }

    return os;
}

void tape_t::desplazar(char direccion)
{
    if(direccion == 'L')
    {
        if(posicion_ == 0)
        {
            insertar_blanco('L');
        }
        else
            posicion_--;
    }
    else if(direccion == 'R')
    {
        posicion_++;

        if(posicion_ == cadena_.size())
        {
            insertar_blanco('R');
        }
    }
}

void tape_t::insertar_blanco(char direccion)
{
    if(direccion == 'L')
    {
        cadena_.push_front(simbolo_blanco);
    }
    else if(direccion == 'R')
    {
        cadena_.push_back(simbolo_blanco);
    }
}


std::ifstream& operator>>(std::ifstream& is, tape_t& rhs)
{
    rhs.read(is);

    return is;
}

}
