#ifndef TUPLE_T_H
#define TUPLE_T_H

#include <fstream>
#include <iostream>

namespace CyA
{

class tuple_t
{
    private:

        unsigned int id_;
        char entrada_;
        char escritura_;
        char movimiento_;
        unsigned int destino_;

    public:

        tuple_t() = default;

        tuple_t(unsigned int id, char r, char w, char mov, unsigned int dest):
            id_(id),
            entrada_(r),
            escritura_(w),
            movimiento_(mov),
            destino_(dest)
        {}

        ~tuple_t() = default;

        tuple_t(const tuple_t& other) = default;

        std::ostream& write(std::ostream& os) const;

        unsigned int get_id()      const  { return id_; }
        char get_lectura()         const  { return entrada_; }
        char get_escritura()       const  { return escritura_; }
        char get_movimiento()      const  { return movimiento_; }
        unsigned int get_destino() const  { return destino_; }

};


std::ostream& operator<<(std::ostream& os, const tuple_t& s);

}

#endif // TUPLE_T_H
