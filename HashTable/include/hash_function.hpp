#pragma once

#include <random>

namespace AyEDA
{

/*******************************************************************************
*   Base Classes
*******************************************************************************/
template<typename K>
class fDispersionBase
{
    public:

        virtual size_t operator()(const K& x) const = 0;
};

template<typename K>
class fScanBase
{
    public:

        virtual size_t operator()(const K& x, size_t i) const = 0;
};


/*******************************************************************************
*   Dispersion Functions
*******************************************************************************/
template<typename K>
class fDispersionSum : public fDispersionBase<K>
{
    public:

        size_t operator()(const K& x) const override
        {
            auto aux = static_cast<unsigned long>(x);
            size_t acc = 0;
            while(aux)
            {
                acc += aux % 10;
                aux /= 10;
            }
            return acc;
        }

};

template<typename K>
class fDispersionModulo : public fDispersionBase<K>
{
    public:

        size_t operator()(const K& x) const override
        {
            return static_cast<unsigned long>(x);
        }
};

template<typename K>
class fDispersionRandom : public fDispersionBase<K>
{
    public:

        size_t operator()(const K& x) const override
        {
            auto temp = static_cast<unsigned long>(x);
            std::default_random_engine e(temp);

            return e();
        }
};


/*******************************************************************************
*   Scan Functions
*******************************************************************************/
template<typename K>
class fScanLinear : public fScanBase<K>
{
    public:

        size_t operator()(const K& x, size_t i) const override
        {
            return i;
        }
};

template<typename K>
class fScanQuadratic : public fScanBase<K>
{
    public:

        size_t operator()(const K& x, size_t i) const override
        {
            return i*i;
        }
};

template<typename K>
class fScanDD : public fScanBase<K>
{
    private:

        fDispersionBase<K>* fDispersion_;

    public:

        explicit fScanDD(fDispersionBase<K>* fd)
            : fDispersion_(fd)
        {}

        ~fScanDD()
        {
            delete fDispersion_;
        }

        size_t operator()(const K& x, size_t i) const override
        {
            return (*fDispersion_)(x) * i;
        }
};

template<typename K>
class fScanRD : public fScanBase<K>
{
    public:

        size_t operator()(const K& x, size_t i) const override
        {
            if(i == 0) { return 0; }
            auto aux = static_cast<unsigned long>(x);
            std::default_random_engine e(aux);

            for(size_t j = 0; j < i; ++j)
            {
                aux = e();
            }

            return aux;
        }
};


} //namespace AyEDA