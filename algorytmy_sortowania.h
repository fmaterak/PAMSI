#pragma once

#include <algorithm>

template<typename T>
void sort_intro(T *tab, T *tmp, int lewo, int prawo, int maxamp);

template<typename T>
void sort_szybki(T *tab, T *tmp, int lewo, int prawo, int maxamp);

template<typename T>
void sort_scalanie(T *tab, T *tmp, int lewo, int prawo, int maxamp);
