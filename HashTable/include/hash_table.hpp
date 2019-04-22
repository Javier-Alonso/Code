#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

#include "cell_t.hpp"
#include "hash_function.hpp"

namespace AyEDA
{

template <typename K>
class HashTable
{
    private:

        cell_t<K>** vCell_;
        size_t nCells_;
        size_t nBlocks_;
        fDispersionBase<K>* fDispersion_;
        fScanBase<K>* fScan_;

    public:

        HashTable(size_t nCells, size_t nBlocks, size_t fd, size_t fs);
        ~HashTable();

        HashTable(const HashTable& other) = delete;
        HashTable operator=(const HashTable& other) = delete;

        bool search(const K& x) const;
        bool insert(const K& x);

    private:

        const cell_t<K>* operator[] (size_t i) const;
        cell_t<K>* operator[](size_t i);

        void set_cells();
        void set_fDispersion(size_t fd);
        void set_fScan(size_t fs);
};


template <typename K>
HashTable<K>::HashTable(size_t nCells, size_t nBlocks, size_t fd, size_t fs)
    : vCell_((nCells == 0)? nullptr : new cell_t<K>*[nCells])
    , nCells_(nCells)
    , nBlocks_(nBlocks)
    , fDispersion_(nullptr)
    , fScan_(nullptr)
{
    if(vCell_ == nullptr)
    {
        throw std::runtime_error("CANNOT INITIALIZE CURRENT OBJECT");
    }

    set_cells();
    set_fDispersion(fd);
    set_fScan(fs);

    if(fDispersion_ == nullptr || fScan_ == nullptr)
    {
        throw std::invalid_argument("INVALID ID FUNCTION!");
    }
}

template <typename K>
HashTable<K>::~HashTable()
{
    for(size_t i = 0; i < nCells_; ++i)
    {
        vCell_[i]->~cell_t<K>();
    }
    delete [] vCell_;
    delete fDispersion_;
    delete fScan_;
}

template <typename K>
bool HashTable<K>::search(const K& x) const
{
    size_t pos = (*fDispersion_)(x);
    size_t i = 0;

    while(i < nCells_ && !((*this)[pos + (*fScan_)(x, i++)]->search(x)));

    return i <= nCells_;
}

template <typename K>
bool HashTable<K>::insert(const K& x)
{
    size_t pos = (*fDispersion_)(x);
    size_t i = 0;

    while(i < nCells_ && !((*this)[pos + (*fScan_)(x, i++)]->insert(x)));

    return i <= nCells_;
}

template <typename K>
const cell_t<K>* HashTable<K>::operator[](size_t i) const
{
    return vCell_[i % nCells_];
}

template <typename K>
cell_t<K>* HashTable<K>::operator[](size_t i)
{
    return vCell_[i % nCells_];
}

template<typename K>
void HashTable<K>::set_fDispersion(size_t fd)
{
    switch(fd)
    {
        case 1:
            fDispersion_ = new fDispersionSum<K>;
            break;
        case 2:
            fDispersion_ = new fDispersionModulo<K>;
            break;
        case 3:
            fDispersion_ = new fDispersionRandom<K>;
            break;
        default:
            break;
    }
}

template<typename K>
void HashTable<K>::set_fScan(size_t fs)
{
    switch(fs)
    {
        case 1:
            fScan_ = new fScanLinear<K>;
            break;
        case 2:
            fScan_ = new fScanQuadratic<K>;
            break;
        case 3:
            fScan_ = new fScanDD<K>(new fDispersionRandom<K>);
            break;
        case 4:
            fScan_ = new fScanRD<K>;
            break;
        default:
            break;
    }
}

template<typename K>
void HashTable<K>::set_cells()
{
    for(size_t i = 0; i < nCells_; ++i)
    {
        vCell_[i] = new cell_t<K>(nBlocks_);
    }
}

} //namespace AyEDA
