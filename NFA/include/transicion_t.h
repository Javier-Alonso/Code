#ifndef TRANSICION_T_H
#define TRANSICION_T_H

#include <iostream>
#include <set>

namespace CyA
{

class transicion_t
{
    private:

        char simbolo_;
        std::set<unsigned int> destino_;

    public:

        transicion_t() = default;
        transicion_t(char s):
            simbolo_(s),
            destino_()
            {}
        transicion_t(char s, std::set<unsigned int> d):
            simbolo_(s),
            destino_(d)
            {}

        ~transicion_t() = default;

        transicion_t(const transicion_t& other) = default;

        bool operator==(const transicion_t& rhs) const;
        bool operator<(const transicion_t& rhs) const;

        std::ostream& write(std::ostream& os) const;

        const std::set<unsigned int>& get_destino() const { return destino_; }
        std::set<unsigned int>& get_destino()             { return destino_; }
        char get_simbolo()                          const { return simbolo_; }

    private:

        void set_destino(const std::set<unsigned int>& val) { destino_ = val; }
        void set_simbolo(char val)                          { simbolo_ = val; }

};

std::ostream& operator<<(std::ostream& os, const transicion_t& t);

}

#endif // TRANSICION_T_H
