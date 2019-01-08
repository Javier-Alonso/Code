#ifndef TRANSICION_T_H
#define TRANSICION_T_H

#include <iostream>

namespace CyA
{

class transicion_t
{
    private:

        char simbolo_;
        unsigned int destino_;

    public:

        transicion_t() = default;

        transicion_t(char s):
            simbolo_(s),
            destino_()
        {}
        transicion_t(char s, unsigned int d):
            simbolo_(s),
            destino_(d)
            {}
        ~transicion_t() = default;

        bool operator==(const transicion_t& rhs) const;
        bool operator<(const transicion_t& rhs) const;

        std::ostream& write(std::ostream& os) const;

        unsigned int get_destino() const { return destino_; }
        char get_simbolo() const         { return simbolo_; }

        void set_destino(unsigned int val) { destino_ = val; }
        void set_simbolo(char val)         { simbolo_ = val; }

};

std::ostream& operator<<(std::ostream& os, const transicion_t& t);

}

#endif // TRANSICION_T_H
