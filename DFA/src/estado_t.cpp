#include "estado_t.h"

namespace CyA
{

estado_t& estado_t::operator=(const estado_t& rhs)
{
    if (this == &rhs) return *this;

    set_id(rhs.get_id());
    set_aceptacion(rhs.es_aceptacion());
    set_muerte(rhs.es_muerte());
    set_delta(rhs.get_delta());

    return *this;
}


estado_t& estado_t::operator=(const unsigned int val)
{
    this->set_id(val);

    return *this;
}


bool estado_t::operator==(const estado_t& rhs) const
{
    return (this->get_id() == rhs.get_id());
}


bool estado_t::operator<(const estado_t& rhs)  const
{
    return (this->get_id() < rhs.get_id());
}


std::ostream& estado_t::write(std::ostream& os) const
{
    os << get_id();

    return os;
}

void estado_t::insert_transicion(char s, unsigned int d)
{
    auto it = std::find(delta_.begin(), delta_.end(), s);

    if (it == delta_.end())
    {
        delta_.emplace_back(s, d);
    }

    else
    {
        it->set_destino(d);
    }
}

unsigned int estado_t::get_transicion(char s) const
{
    auto it = std::find(delta_.begin(), delta_.end(), s);

    if (it == delta_.end())
        return id_invalido;
    else
        return it->get_destino();
}

std::ostream& operator<<(std::ostream& os, const estado_t& s)
{
    s.write(os);

    return os;
}

}
