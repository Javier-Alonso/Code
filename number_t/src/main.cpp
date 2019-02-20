#include <iostream>

#include "number_t.h"

static const size_t BIN = 2;
static const size_t OCT = 8;
static const size_t DEC = 10;
static const size_t HEX = 16;

template<size_t B, size_t N> void testNumber();
template<size_t B, size_t N> void perform_operations(AyEDA::number_t<B, N>& N1, AyEDA::number_t<B, N>& N2);
void get_input(int& v1, int& v2);

int main()
{
    testNumber<BIN,8>();
    testNumber<DEC,4>();
    testNumber<HEX,10>();

    return 0;
}


template<size_t B, size_t N>
void testNumber()
{
    int v1, v2;
    get_input(v1, v2);

    AyEDA::number_t<B, N> N1(v1), N2(v2);
    std::cout << N1 << std::endl << N2 << std::endl;

    perform_operations(N1, N2);
}

void get_input(int& v1, int& v2)
{
    bool valid_input = false;
    std::cin.clear();
    do
    {
        std::cin >> v1 >> v2;

        if(v1 < 0 || v2 < 0)
            std::cerr << "The values cannot be negative. Try again: " << std::endl;
        else
            valid_input = true;
    }
    while(!valid_input);
}

template<size_t B, size_t N>
void perform_operations(AyEDA::number_t<B, N>& N1, AyEDA::number_t<B, N>& N2)
{
    std::cout << N1 << " + " << N2 << " = " << N1 + N2 << std::endl;

    std::cout << N1 << " - " << N2 << " = ";
    if(N1 < N2) std::cout << '-';
    std::cout << N1 - N2 << std::endl;

    std::cout << N1 << " * " << N2 << " = " << N1 * N2 << std::endl;

    std::cout << N1 << " / " << N2 << " = ";
    if(N2 == 0) std::cout << "NaN" << std::endl;
    else        std::cout << N1 / N2 << std::endl;

    std::cout << N1 << " % " << N2 << " = ";
    if(N2 == 0) std::cout << "NaN" << std::endl;
    else        std::cout << N1 % N2 << std::endl;

    std::cout << N1 << " ^ " << N2 << " = ";
    if(N1 == 0 && N2 == 0)  std::cout << "NaN" << std::endl;
    else                    std::cout << N1.pow(N2) << std::endl;

    std::cout << N1 << "! = " << N1.factorial() << std::endl;
}