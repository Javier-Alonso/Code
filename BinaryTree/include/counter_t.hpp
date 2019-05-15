#pragma once

#include <algorithm>
#include <iostream>

namespace AyEDA
{

class counter_t
{
    private:

        size_t count_;
        size_t max_;
        size_t min_;
        size_t acc_;

    public:

        counter_t()
            : count_(0)
            , max_(0)
            , min_(-1)
            , acc_(0)
        {}

        ~counter_t() = default;

        counter_t(const counter_t&) = default;
        counter_t& operator=(const counter_t&) = default;
        counter_t& operator=(const size_t& val) { count_ = val; return *this; }

        void set(size_t i)  { count_ = i; }
        void reset()        { set(0); }
        void full_reset()   { set(0); max_ = 0; min_ = -1; acc_ = 0; }

        size_t get()     const  { return count_; }
        size_t get_max() const  { return max_; }
        size_t get_min() const  { return min_; }
        size_t get_acc() const  { return acc_; }

        void update_parameters()
        {
            min_ = std::min(count_, min_);
            max_ = std::max(count_, max_);
            acc_ += count_;
        }

        counter_t& operator++()
        {
            ++count_;
            return *this;
        }
        const counter_t operator++(int)
        {
            counter_t temp(*this);
            operator++();
            return temp;
        }
};


} //namespace AyEDA