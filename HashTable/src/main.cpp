#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "dni_t.hpp"
#include "hash_table.hpp"

using pair_t = std::pair<size_t, std::string>;
using tuple_t = std::tuple<size_t, float, size_t>;

void get_hash_parameters(size_t& nCells, size_t& nKeys, pair_t& fDispersion, pair_t& fScan);
void get_test_parameters(float& factor, size_t& nTests);
void print_results(size_t, size_t, const pair_t&, const pair_t&, float, size_t, tuple_t&, tuple_t&);

int main()
{
    size_t nCells, nKeys;
    pair_t fDispersion, fScan;
    get_hash_parameters(nCells, nKeys, fDispersion, fScan);

    float factor;
    size_t nTests;
    get_test_parameters(factor, nTests);

    /*******************************************************************************
    *   Bench Generation
    *******************************************************************************/
    const auto N = static_cast<size_t>(factor * nCells * nKeys);
    std::vector<AyEDA::DNI> testBench(static_cast<size_t>(2 * N));

    /*******************************************************************************
    *   Hash Insertion
    *******************************************************************************/
    AyEDA::HashTable<AyEDA::DNI> hash_table(nCells, nKeys, fDispersion.first, fScan.first);
    const auto nInsertions = static_cast<size_t>(nCells * factor);

    for(size_t i = 0; i < nInsertions; ++i)
    {
        hash_table.insert(testBench[i]);
    }

    /*******************************************************************************
    *   Search Test
    *******************************************************************************/
    auto& counter = AyEDA::DNI::cnt_;
    counter = 0;
    std::default_random_engine e(static_cast<unsigned int>(AyEDA::clk::now().time_since_epoch().count()));
    std::uniform_int_distribution<size_t> searchDistribution(0, N);

    for(size_t i = 0; i < nTests; ++i)
    {
        hash_table.search(testBench[searchDistribution(e)]);

        counter.update_parameters();
        counter.reset();
    }
    auto sResult = std::make_tuple(counter.get_min(), ((float)counter.get_acc() / (float)nTests), counter.get_max());

    /*******************************************************************************
    *   Insertion Test
    *******************************************************************************/
    counter.full_reset();
    std::uniform_int_distribution<size_t> insertDistribution(N, 2*N);

    for(size_t i = 0; i < nTests; ++i)
    {
        hash_table.search(testBench[insertDistribution(e)]);

        counter.update_parameters();
        counter.reset();
    }
    auto iResult = std::make_tuple(counter.get_min(), ((float)counter.get_acc() / (float)nTests), counter.get_max());

    /*******************************************************************************
    *   Test Results
    *******************************************************************************/
    print_results(nCells, nKeys, fDispersion, fScan, factor, nTests, sResult, iResult);

    return 0;
}

void
print_results(size_t nCells, size_t nKeys, const pair_t& fDispersion, const pair_t& fScan, float factor, size_t nTests,
              tuple_t& search_result, tuple_t& insert_result)
{
    const size_t indent = 20;

    std::cout << std::setw(indent) << "Cells"
              << std::setw(indent) << "Keys"
              << std::setw(indent) << "Dispersion"
              << std::setw(indent) << "Probing"
              << std::setw(indent) << "Load"
              << std::setw(indent) << "Test" << std::endl;
    std::cout << std::setw(indent) << nCells
              << std::setw(indent) << nKeys
              << std::setw(indent) << fDispersion.second
              << std::setw(indent) << fScan.second
              << std::setw(indent) << factor
              << std::setw(indent) << nTests << std::endl << std::endl;

    std::cout << std::setw(2 * indent) << "Minimum"
              << std::setw(indent) << "Medium"
              << std::setw(indent) << "Maximum" << std::endl;
    std::cout << std::setw(indent) << "Search"
              << std::setw(indent) << std::get<0>(search_result)
              << std::setw(indent) << std::get<1>(search_result)
              << std::setw(indent) << std::get<2>(search_result) << std::endl;
    std::cout << std::setw(indent) << "Insert"
              << std::setw(indent) << std::get<0>(insert_result)
              << std::setw(indent) << std::get<1>(insert_result)
              << std::setw(indent) << std::get<2>(insert_result) << std::endl;
}


void get_hash_parameters(size_t& nCells, size_t& nKeys, pair_t& fDispersion, pair_t& fScan)
{
    std::cout << "\tHash Table Test" << std::endl;

    std::cout << "Number of Cells: ";
    std::cin >> nCells;

    std::cout << "Keys per cell: ";
    std::cin >> nKeys;

    std::cout << "Dispersion Function" << std::endl
              << "\t1. Sum" << std::endl
              << "\t2. Modulo" << std::endl
              << "\t3. Pseudo-Random" << std::endl
              << "\n>>> Choose an option: ";
    std::cin >> fDispersion.first;

    switch(fDispersion.first)
    {
        case 1:  fDispersion.second = "Sum";
                 break;
        case 2:  fDispersion.second = "Modulo";
                 break;
        case 3:  fDispersion.second = "Pseudo-Random";
                 break;
        default: throw std::invalid_argument("INVALID OPTION ID");
    }

    std::cout << "Scan Function" << std::endl
              << "\t1. Linear" << std::endl
              << "\t2. Quadratic" << std::endl
              << "\t3. Double-Dispersion" << std::endl
              << "\t4. Re-Dispersion" << std::endl
              << "\n>>> Choose an option: ";
    std::cin >> fScan.first;

    switch(fDispersion.first)
    {
        case 1:  fScan.second = "Linear";
                 break;
        case 2:  fScan.second = "Quadratic";
                 break;
        case 3:  fScan.second = "Double-Dispersion";
                 break;
        case 4:  fScan.second = "Re-Dispersion";
                 break;
        default: throw std::invalid_argument("INVALID OPTION ID");
    }
}

void get_test_parameters(float& factor, size_t& nTests)
{
    std::cout << "Load factor: ";
    std::cin >> factor;

    std::cout << "Number of Tests: ";
    std::cin >> nTests;
}