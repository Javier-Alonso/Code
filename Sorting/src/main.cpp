#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

#include "dni_t.hpp"
#include "printer.hpp"
#include "sort.hpp"

template<typename K> void reassign(K* v, size_t size);


int main(int argc, char* argv[])
{
    using namespace AyEDA;
    const size_t I = 15;

    if(argc != 4)
    {
        std::cerr << "3 arguments expected, " << argc - 1 << " provided\n";
        exit(1);
    }

    size_t nTest = std::strtol(argv[1], nullptr, 10);
    size_t sequenceSize = std::strtol(argv[2], nullptr, 10);
    char sortID = *argv[3];

    auto sortFunction = Sort<DNI>::create(sortID);
    auto& counter = DNI::cnt_;
    std::unique_ptr<DNI[]> vDNI(new DNI[sequenceSize]());

    counter = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < nTest; ++i)
    {
        sortFunction->sort(vDNI.get(), sequenceSize);
        #ifdef SHOWING
            std::cout << std::endl;
        #endif
        reassign(vDNI.get(), sequenceSize);
        counter.update_parameters();
        counter.reset();
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    float mean = (float)counter.get_acc() / (float)nTest;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    
    std::cout << std::setw(I) << sortFunction->name()
              << std::setw(I) << counter.get_min()
              << std::setw(I) << std::fixed << std::setprecision(2) << mean
              << std::setw(I) << counter.get_max()
              << std::setw(I) << duration << " µs"
              << std::endl;

    counter.full_reset();

    delete sortFunction;

    return 0;
}

template<typename K>
void reassign(K* v, size_t size)
{
    for(size_t i = 0; i < size; ++i)
    {
        v[i] = AyEDA::DNI();
    }
}


