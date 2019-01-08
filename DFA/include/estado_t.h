#ifndef ESTADO_T_H
#define ESTADO_T_H

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "transicion_t.h"

namespace CyA
{

const unsigned int id_invalido = std::numeric_limits<unsigned int>::max();

using tabla_t = std::vector<transicion_t>;

class estado_t
{
    private:

        unsigned int id_;
        bool aceptacion_;
        bool muerte_;
        tabla_t delta_;

    public:

        estado_t() = default;

        estado_t(unsigned int id, bool a = false, bool m = false):
            id_(id),
            aceptacion_(a),
            muerte_(m)
            {}

        ~estado_t() = default;

        estado_t(const estado_t& other) = default;

        estado_t& operator=(const estado_t& other);
        estado_t& operator=(unsigned int val);
        bool operator==(const estado_t& rhs) const;
        bool operator<(const estado_t& rhs)  const;

        std::ostream& write(std::ostream& os) const;

        void insert_transicion(char s, unsigned int d);
        unsigned int get_transicion(char s) const;

        unsigned int get_id() const      { return id_; }
        bool es_aceptacion()  const      { return aceptacion_; }
        bool es_muerte()      const      { return muerte_; }
        const tabla_t& get_delta() const { return delta_; }

        void set_muerte (bool b)         { muerte_ = b; }

    private:

        void set_id (unsigned int val)       { id_ = val; }
        void set_aceptacion (bool val)       { aceptacion_ = val; }
        void set_delta (const tabla_t& val)  { delta_ = val; }
};


std::ostream& operator<<(std::ostream& os, const estado_t& s);

}

#endif // ESTADO_T_H
