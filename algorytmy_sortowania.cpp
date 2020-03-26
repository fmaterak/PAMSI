#include "algorytmy_sortowania.h"
using namespace std;

/**************
* MERGE SORT  *
**************/

template<typename T>
void merge(T *tab, T *tmp, int lewo, int srodek, int prawo)
{
	for (int i = lewo; i <= prawo; i++) tmp[i] = tab[i];

	int i = lewo;
	int j = srodek + 1;
	int q = lewo;

	while (i <= srodek && j <= prawo)
	{
		if (tmp[i] < tmp[j]) tab[q++] = tmp[i++];
		else tab[q++] = tmp[j++];
	}
	while (i <= srodek) tab[q++] = tmp[i++];
}


template<typename T>
void sortowanie_scalanie(T *tab, T *tmp, int lewo, int prawo)
{
	if (lewo < prawo)
	{
		int srodek = (lewo + prawo) / 2;
		sortowanie_scalanie(tab, tmp, lewo, srodek);
		sortowanie_scalanie(tab, tmp, srodek + 1, prawo);
		merge(tab, tmp, lewo, srodek, prawo);
	}
}


template<typename T>
void sort_scalanie(T *tab, T *tmp, int lewo, int prawo, int maxamp)
{
    sortowanie_scalanie(tab, tmp, lewo, prawo);
}

/**************
* QUICK SORT  *
**************/

template<typename T>
int partition(T *tab, int lewo, int prawo)
{
    int pivot = tab[(lewo + prawo) / 2], i = lewo, j = prawo;

    while (true)
    {
        while (tab[j] > pivot) j--;

        while (tab[i] < pivot) i++;

        if (i < j)  swap(tab[i++], tab[j--]);
        else return j;
    }
}


template<typename T>
void szybkie_sortowanie(T *tab, int lewo, int prawo)
{
    if (lewo < prawo)
    {
        int q = partition(tab, lewo, prawo);
        szybkie_sortowanie(tab, lewo, q);
        szybkie_sortowanie(tab, q + 1, prawo);
    }
}


template<typename T>
void sort_szybki(T *tab, T *tmp, int lewo, int prawo, int maxamp)
{
    szybkie_sortowanie(tab, lewo, prawo);
}


/*****************
* INSERTION SORT *
******************/
template<typename T>
void insertionsort(T *tab, int lewo, int prawo)
{
	for (int i = lewo + 1; i <= prawo; i++)
	{
		int key = tab[i];
		int j = i;

		while (j > lewo && tab[j - 1] > key)
        {
            tab[j] = tab[j - 1];
            j--;
        }
		tab[j] = key;
	}
}


/************
* HEAP SORT *
************/
template<typename T>
void heapsort(T *lewo, T *prawo)
{
	make_heap(lewo, prawo);
	sort_heap(lewo, prawo);
}


/**************
* INTRO SORT  *
**************/
template<typename T>
void introsortowanie(T *tab, T *lewo, T *prawo, int maxamp)
{
	if ((prawo - lewo) < 16) insertionsort(tab, lewo - tab, prawo - tab);
	else if (maxamp == 0) heapsort(lewo, prawo + 1);
	else
    {
		int pivot = partition(tab, lewo - tab, prawo - tab);
		introsortowanie(tab, lewo, tab + pivot, maxamp - 1);
		introsortowanie(tab, tab + pivot + 1, prawo, maxamp - 1);
    }
}


template<typename T>
void sort_intro(T *tab, T *tmp, int lewo, int prawo, int maxamp)
{
    introsortowanie(tab, tab, tab + prawo , maxamp);
}


template void sort_intro<int>(int*, int*, int, int, int);
template void sort_scalanie<int>(int*, int*, int, int, int);
template void sort_szybki<int>(int*, int*, int, int, int);

template void sort_intro<double>(double*, double*, int, int, int);
template void sort_scalanie<double>(double*, double*, int, int, int);
template void sort_szybki<double>(double*, double*, int, int, int);
