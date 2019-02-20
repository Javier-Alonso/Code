#pragma once

#include <array>
#include <cmath>
#include <iostream>

namespace AyEDA
{

template<size_t B, size_t N, typename T> class number_t;
template<size_t B, size_t N, typename T> std::ostream& operator<<(std::ostream& os, const number_t<B, N, T>& rhs);


template<size_t B, size_t N, typename T = char>
class number_t
{
    private:

        std::array<T, N> digits_;
        bool overflow_ = false;

    public:

        number_t(int val = 0):
        digits_{}
        {
            to_base(val);
        }

        ~number_t() = default;

        number_t(const number_t& other) = default;
        number_t& operator=(const number_t& other) = default;

        friend std::ostream& operator<< <>(std::ostream& os, const number_t& rhs);

        number_t operator+(const number_t& rhs) const;
        number_t operator-(const number_t& rhs) const;
        number_t operator*(const number_t& rhs) const;
        number_t operator/(const number_t& rhs) const;
        number_t operator%(const number_t& rhs) const;
        number_t pow(const number_t& rhs) const;
        number_t factorial() const;

        const number_t operator++(int);
        const number_t operator--(int);
        number_t& operator++();
        number_t& operator--();

        number_t& operator+=(const number_t& rhs);
        number_t& operator-=(const number_t& rhs);
        number_t& operator*=(const number_t& rhs);
        number_t& operator/=(const number_t& rhs);
        number_t& operator%=(const number_t& rhs);

        bool operator<(const number_t& rhs) const;
        bool operator>(const number_t& rhs) const;
        bool operator<=(const number_t& rhs) const;
        bool operator>=(const number_t& rhs) const;

        bool operator==(const number_t& rhs) const;
        bool operator!=(const number_t& rhs) const;

    private:

        const T& operator[](size_t index) const;
        T& operator[](size_t index);

        void to_base(int val);
        char convert_digit(T val) const;
        void check_overflow(int val) const;

        void fix_carry(int index);
        void fix_borrow(int index);

};


/*******************************************************************************
*   I/O Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
std::ostream& operator<< (std::ostream& os, const number_t<B, N, T>& rhs)
{
    os << '(';

    for(const auto& digit: rhs.digits_)
    {
        os << rhs.convert_digit(digit);
    }

    os << ')';

    if(rhs.overflow_)
    {
        os << " OVERFLOW ERROR!";
    }

    return os;
}


/*******************************************************************************
*   Arithmetic Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::operator+(const number_t<B, N, T>& rhs) const
{
    number_t<B, N, T> result(*this);
    auto index = static_cast<int>(N - 1);

    for(; index >= 0; --index)
    {
        if(overflow_) break;
        result[index] += rhs[index];
        result.fix_carry(index);
    }

    return result;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::operator-(const number_t<B, N, T>& rhs) const
{
    if(*this < rhs) return (rhs - *this);

    number_t<B, N, T> result(*this);
    auto index = static_cast<int>(N - 1);

    for(; index >= 0; --index)
    {
        if(overflow_) break;
        result[index] -= rhs[index];
        result.fix_borrow(index);
    }

    return result;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::operator*(const number_t<B, N, T>& rhs) const
{
    number_t<B, N, T> result;

    for(number_t<B, N, T> i; i < rhs; i++)
    {
        if(result.overflow_) break;
        result += *this;
    }

    return result;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::operator/(const number_t<B, N, T>& rhs) const
{
    number_t<B, N, T> dividend(*this);
    number_t<B, N, T> result;

    while(dividend >= rhs)
    {
        dividend -= rhs;
        ++result;
    }

    return result;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::operator%(const number_t<B, N, T>& rhs) const
{
    number_t<B, N, T> remainder(*this);

    while(remainder >= rhs)
    {
        remainder -= rhs;
    }

    return remainder;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::pow(const number_t& rhs) const
{
    if(rhs == 0)
    {
        return 1;
    }

    number_t<B, N, T> result(*this);
    number_t<B, N, T> cnt;

    while(++cnt < rhs)
    {
        if(result.overflow_) break;
        result *= *this;
    }

    return result;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T> number_t<B, N, T>::factorial() const
{
    if(*this == 0)
    {
        return 1;
    }

    number_t<B, N, T> result(*this);
    number_t<B, N, T> cnt(1);

    for (; cnt < *this; ++cnt)
    {
        if(result.overflow_) break;
        result *= *this - cnt;
    }

    return result;
}


/*******************************************************************************
*   Increment Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
const number_t<B, N, T> number_t<B, N, T>::operator++(int)
{
    number_t<B, N, T> tmp(*this);

    operator++();

    return tmp;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator++()
{
    digits_.back()++;

    fix_carry(static_cast<int>(N - 1));

    return *this;
}

template<size_t B, size_t N, typename T>
const number_t<B, N, T> number_t<B, N, T>::operator--(int)
{
    number_t<B, N, T> tmp(*this);

    operator--();

    return tmp;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator--()
{
    digits_.back()--;

    fix_borrow(static_cast<int>(N - 1));

    return *this;
}


/*******************************************************************************
*   Binary Arithmetic Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator+=(const number_t<B, N, T>& rhs)
{
    return *this = *this + rhs;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator-=(const number_t<B, N, T>& rhs)
{
    return *this = *this - rhs;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator*=(const number_t<B, N, T>& rhs)
{
    return *this = *this * rhs;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator/=(const number_t<B, N, T>& rhs)
{
    return *this = *this / rhs;
}

template<size_t B, size_t N, typename T>
number_t<B, N, T>& number_t<B, N, T>::operator%=(const number_t<B, N, T>& rhs)
{
    return *this = *this % rhs;
}


/*******************************************************************************
*   Relational Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
bool number_t<B, N, T>::operator<(const number_t& rhs) const
{
    return digits_ < rhs.digits_;
}

template<size_t B, size_t N, typename T>
bool number_t<B, N, T>::operator>(const number_t& rhs) const
{
    return rhs < *this;
}

template<size_t B, size_t N, typename T>
bool number_t<B, N, T>::operator<=(const number_t& rhs) const
{
    return !(rhs < *this);
}

template<size_t B, size_t N, typename T>
bool number_t<B, N, T>::operator>=(const number_t& rhs) const
{
    return !(*this < rhs);
}


/*******************************************************************************
*   Equality Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
bool number_t<B, N, T>::operator==(const number_t& rhs) const
{
    return digits_ == rhs.digits_;
}

template<size_t B, size_t N, typename T>
bool number_t<B, N, T>::operator!=(const number_t& rhs) const
{
    return !(rhs == *this);
}


/*******************************************************************************
*   Access Operators
*******************************************************************************/
template<size_t B, size_t N, typename T>
const T& number_t<B, N, T>::operator[](size_t index) const
{
    return digits_[index];
}

template<size_t B, size_t N, typename T>
T& number_t<B, N, T>::operator[](size_t index)
{
    return digits_[index];
}


/*******************************************************************************
*   Auxiliary Methods
*******************************************************************************/
template<size_t B, size_t N, typename T>
void number_t<B, N, T>::to_base(int val)
{
    check_overflow(val);

    size_t index = N - 1;

    while(val)
    {
        digits_[index--] = (val % B);
        val /= B;
    }
}

template<size_t B, size_t N, typename T>
char number_t<B, N, T>::convert_digit(T val) const
{
    if(val >= 10)
    {
        return static_cast<char>(val - 10 + 'A');
    }
    else
    {
        return static_cast<char>(val + '0');
    }
}

template<size_t B, size_t N, typename T>
void number_t<B, N, T>::check_overflow(int val) const
{
    if(val / std::pow(B, N - 1) > B)
    {
        //throw std::overflow_error("OVERFLOW ERROR!");
        std::cerr << "OVERFLOW ERROR!" << std::endl;
    }
}

template<size_t B, size_t N, typename T>
void number_t<B, N, T>::fix_carry(int index)
{
    if (index >= 0)
    {
        if (digits_[index] >= B)
        {
            if(index - 1 >= 0)
            {
                digits_[index] %= B;
                digits_[index - 1]++;
                fix_carry(index - 1);
            }
            else
            {
                overflow_ = true;
            }
        }
    }
}

template<size_t B, size_t N, typename T>
void number_t<B, N, T>::fix_borrow(int index)
{
    if (index >= 0)
    {
        if (digits_[index] < 0)
        {
            if(index >= 1)
            {
                digits_[index] += B;
                digits_[index - 1]--;
                fix_borrow(index - 1);
            }
            else
            {
                overflow_ = true;
            }
        }
    }
}

} //namespace AyEDA
