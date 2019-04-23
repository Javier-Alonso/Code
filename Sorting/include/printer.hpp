#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << '[';
    for(size_t i = 0; i < v.size() - 1; ++i)
    {
        os << v[i] << ", ";
    }
    os << v.back() << ']';

    return os;
}

template <typename T>
std::ostream& write(std::ostream& os, const T* arr, size_t size)
{
    os << '[';
    for(size_t i = 0; i + 1 < size; ++i)
    {
        os << arr[i] << ", ";
    }
    os << arr[size - 1] << ']';

    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v)
{
    os << '[';
    for(auto it = v.begin(); it != --v.end(); ++it)
    {
        os << *it << ", ";
    }
    os << *v.end() << ']';

    return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T, S>& v)
{
    for(const auto& i : v)
    {
        os << i.first << " : " << i.second << "\n";
    }

    return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T, S>& v)
{
    os << "(" << v.first << ", " << v.second << ")";

    return os;
}