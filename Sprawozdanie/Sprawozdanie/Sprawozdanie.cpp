#include "stdafx.h"
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const int n = 4;

	double wektorWspolczynnikow[n] = { 1, 8, 6, 1 };
	double wektorWynikow[n];
	double macierzOdwrotna[n][2 * n] = { 
		{ 1, 0, 0, 0 },
		{ 1, 2, 1, 0 },
		{ 0, 1, 2, 1 },
		{ 0, 0, 1, 1 },
	};

	chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

		// Odwróæ macierz
		double c, d;
		for (int i = 0; i < n; i++) {
			macierzOdwrotna[i][n + i] = 1;
		}

		for (int s = 0; s < n; s++) {
			c = macierzOdwrotna[s][s];
			macierzOdwrotna[s][s] = macierzOdwrotna[s][s] - 1.0;
			for (int j = s + 1; j < 2 * n; j++) {
				d = macierzOdwrotna[s][j] / c;
				for (int i = 0; i < n; i++) {
					macierzOdwrotna[i][j] = macierzOdwrotna[i][j] - (d * macierzOdwrotna[i][s]);
				}
			}
		}

		// Przemnó¿ macierz odwrócon¹ przez macierz wspó³czynników.
		double sum = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sum = 0;
				for (int s = 0; s < n; s++) {
					sum += macierzOdwrotna[i][s + n] * wektorWspolczynnikow[s];
				}
				wektorWynikow[i] = sum;
			}
		}

	chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
	cout << "Czas potrzebny do obliczenia ukladu rownan macierza odwrotna: " <<
		chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
	
	for (int i = 0; i < n; i++) {
		cout << "X[" << i << "] : " << wektorWynikow[i] << endl;
	}

	system("pause");

	return 0;
}

