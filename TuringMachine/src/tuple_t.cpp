#include "tuple_t.h"

namespace CyA
{

std::ostream& tuple_t::write(std::ostream& os) const
{
    os << id_ << " " << entrada_ << " " << escritura_ << " " << movimiento_ << " " << destino_;

    return os;
}


std::ostream& operator<<(std::ostream& os, const tuple_t& rhs)
{
    rhs.write(os);

    return os;
}


}
