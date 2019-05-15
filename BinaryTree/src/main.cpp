#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>

#include "binary_tree.hpp"
#include "dni_t.hpp"

template<typename TREE> void demo();
template<typename TREE> void statistic(int argc, char *const *argv);

int main(int argc, char* argv[])
{
    using TreeTemplate = AyEDA::AVLTree<AyEDA::DNI>;

    #ifdef DEMO
        demo<TreeTemplate>();
    #else
        statistic<TreeTemplate>(argc, argv);
    #endif

    return 0;
}

template<typename TREE>
void demo()
{
    TREE AVL;
    bool flag = false;
    char option;
    AyEDA::DNI val;

    do
    {
        std::cin.clear();
        std::cout << "\nBinary Search Tree" << std::endl;
        std::cout << "\t[0] Exit" << std::endl;
        std::cout << "\t[1] Insert Key" << std::endl;
        std::cout << "\t[2] Remove Key" << std::endl;

        std::cin >> option;
        std::cin.clear();

        switch (option)
        {
            case '0' :
                flag = true;
                std::cout << "Closing simulation..." << std::endl;
                break;

            case '1' :
                std::cin >> val;
                AVL.insert(val);
                AVL.writeLevels(std::cout);
                break;

            case '2' :
                std::cin >> val;
                AVL.remove(val);
                AVL.writeLevels(std::cout);
                break;

            default :
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
    while (!flag);
}

template<typename TREE>
void statistic(int argc, char *const *argv)
{
    const size_t I = 15;

    if(argc != 3)
    {
        std::cerr << "2 arguments expected, " << argc - 1 << " provided\n";
        exit(1);
    }

    size_t nTest = strtol(argv[2], nullptr, 10);
    size_t treeSize = strtol(argv[1], nullptr, 10);
    std::unique_ptr<AyEDA::DNI[]> testBench(new AyEDA::DNI[2 * treeSize]());

    TREE AVL;
    for(size_t i = 0; i < treeSize; ++i)
    {
        AVL.insert(testBench[i]);
    }

    std::random_device rd;
    std::default_random_engine e(rd());

    /*******************************************************************************
    *   Search Test
    *******************************************************************************/
    auto& counter = AyEDA::DNI::cnt_;
    counter = 0;

    std::uniform_int_distribution<size_t> searchDistribution(0, treeSize);

    auto t1 = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < nTest; ++i)
    {
        AVL.search(testBench[searchDistribution(e)]);

        counter.update_parameters();
        counter.reset();
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    double mean = (double) counter.get_acc() / (double) nTest;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << std::setw(3 * I) << "TEST RESULTS" << std::endl;
    std::cout << std::setw(2 * I) << "Tree Size"
              << std::setw(I) << "Tests"
              << std::setw(I) << "Minimum"
              << std::setw(I) << "Medium"
              << std::setw(I) << "Maximum"
              << std::setw(I) << "Time"
              << std::endl;
    std::cout << std::setw(I) << "Searching"
              << std::setw(I) << treeSize
              << std::setw(I) << nTest
              << std::setw(I) << counter.get_min()
              << std::setw(I) << std::fixed << std::setprecision(2) << mean
              << std::setw(I) << counter.get_max()
              << std::setw(I) << duration << " µs"
              << std::endl;

    counter.full_reset();

    /*******************************************************************************
    *   Insertion Test
    *******************************************************************************/
    std::uniform_int_distribution<size_t> insertDistribution(0, treeSize);

    t1 = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < nTest; ++i)
    {
        AVL.search(testBench[insertDistribution(e)]);

        counter.update_parameters();
        counter.reset();
    }
    t2 = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    mean = (double) counter.get_acc() / (double) nTest;

    std::cout << std::setw(I) << "Insertion"
              << std::setw(I) << treeSize
              << std::setw(I) << nTest
              << std::setw(I) << counter.get_min()
              << std::setw(I) << std::fixed << std::setprecision(2) << mean
              << std::setw(I) << counter.get_max()
              << std::setw(I) << duration << " µs"
              << std::endl;
}
