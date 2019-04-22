#pragma once

#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>

#include "counter_t.hpp"

namespace AyEDA
{

using clk = std::chrono::high_resolution_clock;

class DNI
{
    private:

        std::array<char, 8> id_;

    public:

        static counter_t cnt_;

        DNI()
            : id_()
        {
            std::default_random_engine e(static_cast<unsigned int>(clk::now().time_since_epoch().count()));
            std::uniform_int_distribution<char> distribution('0','9');

            for(auto& digit: id_)
            {
                digit = static_cast<char>(distribution(e));
            }
        }
        ~DNI() = default;

        explicit operator unsigned long() const
        {
            unsigned long result;
            std::stringstream ss;

            for(const auto& i : id_) { ss << i; }
            ss >> result;

            return result;
        }

        friend bool operator==(const DNI& lhs, const DNI& rhs)  { ++cnt_; return lhs.id_ == rhs.id_; }
        friend bool operator!=(const DNI& lhs, const DNI& rhs)  { return !(lhs == rhs); }

        friend bool operator<(const DNI& lhs, const DNI& rhs)   { ++cnt_; return lhs.id_ < rhs.id_;}
        friend bool operator>(const DNI& lhs, const DNI& rhs)   { return rhs < lhs;}
        friend bool operator<=(const DNI& lhs, const DNI& rhs)  { return !(rhs < lhs);}
        friend bool operator>=(const DNI& lhs, const DNI& rhs)  { return !(lhs < rhs);}

        friend std::ostream& operator<<(std::ostream& os, const DNI& rhs)
        {
            for(const auto& digit: rhs.id_) { os << digit; }
            return os;
        }
};


counter_t DNI::cnt_ = counter_t();

} //namespace AyEDA
