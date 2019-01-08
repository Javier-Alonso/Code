#ifndef CADENA_T_H
#define CADENA_T_H

#include <algorithm>
#include <iostream>
#include <string>

namespace CyA
{

const char epsilon = '~';

class cadena_t
{
    private:

        std::string cadena_;

    public:

        cadena_t() = default;

        cadena_t(std::string s):
            cadena_(s)  {}

        ~cadena_t() = default;

        cadena_t(const cadena_t& other):
            cadena_(other.get_cadena())  {}
        cadena_t& operator=(const cadena_t& other);
        bool operator==(const cadena_t& rhs) const;
        bool operator<(const cadena_t& rhs) const;

        const std::string& get_cadena() const  { return cadena_; }
        std::string& get_cadena()              { return cadena_; }

        auto begin() const  { return cadena_.cbegin(); }
        auto end()   const  { return cadena_.cend(); }
        auto begin()        { return cadena_.begin(); }
        auto end()          { return cadena_.end(); }

        auto at(size_t pos)             { return cadena_.at(pos); }
        const auto at(size_t pos) const { return cadena_.at(pos); }

        char& front()               { return cadena_.front(); }
        const char& front() const   { return cadena_.front(); }

        const char* c_str() const   { return cadena_.c_str(); }
        void invertir (void);

        size_t size (void) const    { return cadena_.size(); }
        void resize(size_t n)       { cadena_.resize(n); }

        bool empty(void) const      { return cadena_.empty(); }

    private:

        void set_cadena(std::string val) { cadena_ = val; }

};


cadena_t inversa(const cadena_t& c);
cadena_t operator+(const cadena_t& lhs, const cadena_t& rhs);
std::ostream& operator<<(std::ostream& os, const cadena_t& c);
std::istream& operator>>(std::istream& is, cadena_t& c);

}

#endif // CADENA_T_H
