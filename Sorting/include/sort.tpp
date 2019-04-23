#pragma once

namespace AyEDA
{


/*******************************************************************************
*   Abstract Class
*******************************************************************************/
template<typename K>
Sort<K>* Sort<K>::create(char id)
{
    switch(id)
    {
        case '1': return new SelectionSort<K>;
        case '2': return new ShakeSort<K>;
        case '3': return new HeapSort<K>;
        case '4': return new MergeSort<K>;
        case '5': return new ShellSort<K>;
        case '6': return new StableSort<K>;
        case '7': return new StdSort<K>;
        default:  throw std::invalid_argument("INVALID ID OPTION!");
    }
}

/*******************************************************************************
*   Selection Sort
*******************************************************************************/
template <typename K>
void SelectionSort<K>::sort(K* v, size_t size)
{
    size_t min;

    for(size_t i = 0; i < size - 1; ++i)
    {
        min = i;
        for(size_t j = i + 1; j < size; ++j)
        {
            if(v[j] < v[min])
            {
                min = j;
            }
        }
        std::swap(v[min], v[i]);
        #ifdef SHOWING
            write(std::cout, v, size);
            std::cin.get();
        #endif
    }
}


/*******************************************************************************
*   Shake Sort
*******************************************************************************/
template <typename K>
void ShakeSort<K>::sort(K* v, size_t size)
{
    bool swapped = true;
    int start = 0;
    int end = size - 1;

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            if (v[i] > v[i + 1])
            {
                std::swap(v[i], v[i + 1]);
                swapped = true;
            }
        }

        #ifdef SHOWING
            write(std::cout, v, size);
            std::cin.get();
        #endif

        if (!swapped)
        {
            break;
        }

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (v[i] > v[i + 1])
            {
                std::swap(v[i], v[i + 1]);
                swapped = true;
            }
        }

        #ifdef SHOWING
            write(std::cout, v, size);
            std::cin.get();
        #endif

        ++start;
    }
}


/*******************************************************************************
*   Heap Sort
*******************************************************************************/
template <typename K>
void HeapSort<K>::sort(K* v, size_t size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        build_heap(v, i, size);
    }
    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(v[0], v[i]);
        build_heap(v, 0, i - 1);
        #ifdef SHOWING
            write(std::cout, v, size);
            std::cin.get();
        #endif
    }
}

template <typename K>
void HeapSort<K>::build_heap(K* v, int i, int size)
{
    while (2 * i <= size)
    {
        int h;
        auto h1 = 2 * i;
        auto h2 = h1 + 1;

        if (h1 == size)
        {
            h = h1;
        }
        else if (v[h1] > v[h2])
        {
            h = h1;
        }
        else
        {
            h = h2;
        }

        if (v[h] <= v[i])
        {
            break;
        }
        else
        {
            std::swap(v[i], v[h]);
            i = h;
        }
    }
}


/*******************************************************************************
*   Merge Sort
*******************************************************************************/
template <typename K>
void MergeSort<K>::sort(K* v, size_t size)
{
    mergeSort(v, 0, size - 1, size);
}

template <typename K>
void MergeSort<K>::mergeSort(K* v, int l, int r, size_t size)
{
    int m;

    if(l < r)
    {
        m = (l + r) / 2;

        mergeSort(v, l, m, size);
        mergeSort(v, m + 1, r, size);

        merge(v, l, r, m);
        #ifdef SHOWING
            write(std::cout, v, size);
            std::cin.get();
        #endif
    }

}

template <typename K>
void MergeSort<K>::merge(K* v, int l, int r, int m)
{
    int i = l;
    int j = m + 1;
    int k = 0;

    K aux[r - l + 1];

    while(i <= m && j <= r)
    {
        if(v[i] < v[j])
        {
            aux[k++] = v[i++];
        }
        else
        {
            aux[k++] = v[j++];
        }
    }

    while(i <= m)
    {
        aux[k++] = v[i++];
    }
    while(j <= r)
    {
        aux[k++] = v[j++];
    }

    for(i = l; i <= r; ++i)
    {
        v[i] = aux[i - l];
    }
}


/*******************************************************************************
*   Shell Sort
*******************************************************************************/
template <typename K>
void ShellSort<K>::sort(K* v, size_t size)
{
    size_t del = size;
    double alpha = 0.45454;
    while (del > 1)
    {
        del = static_cast<size_t>(del * alpha);
        delta_sort(v, del, size);
        #ifdef SHOWING
            write(std::cout, v, size);
            std::cin.get();
        #endif
    }
}

template <typename K>
void ShellSort<K>::delta_sort(K* v, int d, int size)
{
    for (int i = d; i < size; i++)
    {
        auto x = v[i] ;
        int j = i;

        while ((j >= d) && (x < v[j-d]))
        {
            v[j] = v[j-d] ;
            j -= d ;
        }

        v[j] = x ;
    }
}



} //namespace AyEDA