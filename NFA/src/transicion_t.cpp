#include "transicion_t.h"

namespace CyA
{

bool transicion_t::operator==(const transicion_t& rhs) const
{
    return (this->get_simbolo() == rhs.get_simbolo());
}

bool transicion_t::operator<(const transicion_t& rhs) const
{
    return (this->get_simbolo() < rhs.get_simbolo());
}

std::ostream& transicion_t::write(std::ostream& os) const
{
    for (const auto& i: get_destino())
    {
        os << get_simbolo() << " " << i << " ";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const transicion_t& t)
{
    t.write(os);

    return os;
}

}
