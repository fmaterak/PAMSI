#include "algorytmy_sortowania.h"
#include <chrono>
#include <fstream>
#include <cmath>
#include <iostream>

#define DataType int

using namespace std;


template<typename T>
using SortFncpunkt = void (*)(T*, T*, int, int, int);


template<typename T>
void drukuj_tablice(T *tab, int n) //funkcja dla testow
{
    for (int i = 0; i < n; i++) cout << tab[i] << " ";
}

template<typename T>
T *stworz_tablice(int n)
{
	return new T[n];
}

template<typename T>
void usun_tablice(T *table)
{
	delete[] table;
}



template<typename T>
void uzupelnij_losowo(T *tab, int n)
{
	for (int i = 0; i < n; i++) tab[i] = rand() % 100000 + 1;
}


template<typename T>
void sort_procent(T *tab, int n, double procent)
{
    if (procent == 100)
    {
        sort(tab, tab + n, greater<T>());
        return;
    }
	sort(tab, tab + (int)((n*procent) / 100));
}


template<typename T>
void sprawdz_posortowanie(T *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            cout << "Tablica nieposortowana!\nZamykanie programu...";
            cin.get();
            exit(1);
        }
    }
}


void check_if_open (ofstream &plik)
{
    if (!plik.is_open())
     {
        cout << "plik nie jest otwarty!\nZamykanie programu...";
        cin.get();
        exit(1);
     }
}


template<typename T>
double sort_it(SortFncpunkt<DataType> fp, int n, T *tab, T *tmp)
{
    auto t_start = chrono::high_resolution_clock::now();
    fp(tab, tmp, 0, n-1, log(n) * 2);
    auto t_end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t_end - t_start).count();
}


int main()
{
    ofstream plik("Wyniki.txt");
    check_if_open(plik);

    srand(time(NULL));

	int petle = 100;
    double ntab[5] = {10000, 50000, 100000, 500000, 1000000};
	double procenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100 /*dla 100 tablica jest posortowana odwrotnie*/};

	SortFncpunkt<DataType> mpunkt= &sort_scalanie, qpunkt = &sort_szybki, ipunkt = &sort_intro;
    SortFncpunkt<DataType> ptable[3] = {qpunkt, mpunkt, ipunkt};

	double licznik = 0;
	int iter = 0;
	string sorts[3] = {"QUCIK_SORT", "MERGE_SORT", "INTRO_SORT"};

    for(SortFncpunkt<DataType> fp : ptable)
    {
        cout << sorts[iter++] <<"--------------------"<< endl<<endl;
        for (double procent : procenttab)
        {
            for (int n : ntab)
            {
                DataType *tab = stworz_tablice<DataType>(n);
                DataType *tmp = stworz_tablice<DataType>(n);

                for (int i = 0; i < petle; i++)
                {
                    uzupelnij_losowo<DataType>(tab, n);
                    sort_procent<DataType>(tab, n, procent);
                    licznik += sort_it<DataType>(fp, n, tab, tmp);
                    sprawdz_posortowanie<DataType>(tab, n);
                    cout << i << "%" << "\r";
                }
                usun_tablice<DataType>(tab);
                usun_tablice<DataType>(tmp);

                cout << n << " tabel posortowanych!" << endl;

                plik << licznik / petle << " "; //sredni czas dla jednej tablicy
                licznik = 0;
            }
            cout << procent << " % zrobione!" << endl<<endl;
        }
        plik << "\n";
    }
    cout << "Koniec sortowania!";
	cin.get();
	plik.close();

	return 0;
}

