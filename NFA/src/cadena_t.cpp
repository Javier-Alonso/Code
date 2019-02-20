#include "cadena_t.h"

namespace CyA
{

cadena_t& cadena_t::operator=(const cadena_t& rhs)
{
    if (this == &rhs) return *this;

    cadena_ = rhs.cadena_;

    return *this;
}

bool cadena_t::operator==(const cadena_t& rhs) const
{
    return (this->get_cadena() == rhs.get_cadena());
}

bool cadena_t::operator<(const cadena_t& rhs) const
{
    return (this->get_cadena() < rhs.get_cadena());
}

void cadena_t::invertir(void)
{
    std::reverse(begin(), end());
}



cadena_t inversa(const cadena_t& c)
{
    cadena_t tmp;

    tmp.resize(c.size());

    std::reverse_copy(c.begin(), c.end(), tmp.begin());

    return tmp;;
}


cadena_t operator+(const cadena_t& lhs, const cadena_t& rhs)
{
    std::string temp = lhs.get_cadena() + rhs.get_cadena();

    return (cadena_t(temp));
}


std::ostream& operator<<(std::ostream& os, const cadena_t& c)
{
    os << ((c.get_cadena().empty())? "&" : c.get_cadena());

    return os;
}

std::istream& operator>>(std::istream& is, cadena_t& c)
{
    is >> c.get_cadena();

    return is;
}


}
