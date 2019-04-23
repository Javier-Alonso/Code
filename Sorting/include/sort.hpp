#pragma once

#include <algorithm>
#include <string>

#include "printer.hpp"

namespace AyEDA
{

template<typename K> class Sort;
template<typename K> class SelectionSort;
template<typename K> class ShakeSort;
template<typename K> class HeapSort;
template<typename K> class MergeSort;
template<typename K> class ShellSort;


template<typename K>
class Sort
{
    public:
        virtual ~Sort() = default;

        static Sort* create(char id);
        virtual void sort(K* v, size_t size) = 0;
        virtual std::string name() const = 0;
};


template<typename K>
class SelectionSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override;
        std::string name() const override { return "Selection Sort"; }
};


template<typename K>
class ShakeSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override;
        std::string name() const override { return "Shake Sort"; }
};


template<typename K>
class HeapSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override;
        std::string name() const override { return "Heap Sort"; }

    private:
        void build_heap(K* v, int i, int size);
};


template<typename K>
class MergeSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override;
        std::string name() const override { return "Merge Sort"; }

    private:
        void mergeSort(K *v, int l, int r, size_t size);
        void merge(K *v, int l, int r, int m);
};


template<typename K>
class ShellSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override;
        std::string name() const override { return "Shell Sort"; }

    private:
        void delta_sort(K* v, int d, int size);
};

template<typename K>
class StableSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override
        {
            std::stable_sort(v, v + size);
        }
        std::string name() const override { return "Stable Sort"; }
};


template<typename K>
class StdSort : public Sort<K>
{
    public:
        void sort(K* v, size_t size) override
        {
            std::sort(v, v + size);
        }
        std::string name() const override { return "Std Sort"; }
};


} //namespace AyEDA


#include "sort.tpp"