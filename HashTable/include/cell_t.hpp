#pragma once

#include <iostream>

namespace AyEDA
{

template <typename K>
class cell_t
{
    private:

        size_t nKeys_;
        size_t last_;
        K* vKey_;

    public:

        explicit cell_t(size_t n = 0);

        ~cell_t();

        cell_t(const cell_t& other) = delete;
        cell_t operator=(const cell_t& other) = delete;

        bool search(const K& x) const;
        bool insert(const K& x);

        bool full() const;

    private:

        size_t find(const K& x) const;

};

template <typename K>
cell_t<K>::cell_t(size_t n)
    : nKeys_(n)
    , last_(0)
    , vKey_((n == 0)? nullptr : new K[n]())
{
    if(vKey_ == nullptr)
    {
        throw std::runtime_error("CANNOT INITIALIZE ARRAY");
    }
}

template <typename K>
cell_t<K>::~cell_t()
{
    delete [] vKey_;
}

template <typename K>
bool cell_t<K>::search(const K& x) const
{
    return find(x) != last_;
}

template <typename K>
bool cell_t<K>::insert(const K& x)
{
    if(full())
    {
        return false;
    }
    else
    {
        //if(find(x) == last_) { return false; }
        vKey_[last_++] = x;
        return true;
    }
}

template <typename K>
bool cell_t<K>::full() const
{
    return last_ == nKeys_;
}

template<typename K>
size_t cell_t<K>::find(const K& x) const
{
    for(size_t i = 0; i < last_; ++i)
    {
        if(x == vKey_[i])
        {
            return i;
        }
    }

    return last_;
}


} //namespace AyEDA
