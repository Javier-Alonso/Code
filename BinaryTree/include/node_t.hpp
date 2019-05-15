#pragma once

#include <iostream>

namespace AyEDA
{

template<typename T>
class node_t
{
    protected:

        T data_;
        node_t* left_;
        node_t* right_;

    public:

        explicit node_t(const T& data)
            : data_(data), left_(nullptr), right_(nullptr) {}

        ~node_t() = default;

        T& get_data()             { return data_; }
        const T& get_data() const { return data_; }

        node_t* const& left()  const { return left_;  }
        node_t* const& right() const { return right_; }

        node_t*& left()  { return left_;  }
        node_t*& right() { return right_; }

        friend std::ostream& operator<<(std::ostream& os, const node_t* node)
        {
            os << '['; if(node == nullptr) os << '.'; else os << node->get_data(); os << ']';
            return os;
        }
};

template<typename T>
class AVLnode_t : public node_t<T>
{
    private:

        int balance_;
        AVLnode_t* left_;
        AVLnode_t* right_;

    public:

        explicit AVLnode_t(const T& data)
            : node_t<T>(data) , balance_(0), left_(nullptr), right_(nullptr) {}

        ~AVLnode_t() = default;

        AVLnode_t* const& left()  const  { return left_;  }
        AVLnode_t* const& right() const  { return right_; }

        AVLnode_t*& left()   { return left_;  }
        AVLnode_t*& right()  { return right_; }

        int get_balance() const   { return balance_; }
        void set_balance(int val) { balance_ = val;  }
};



} //namespace AyEDA
