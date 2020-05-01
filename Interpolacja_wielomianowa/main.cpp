#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

void wypisz(double ** T, const int n, const int m);
void utworz(double **& T, const int n, const int m);
void usun(double ** T, const int n);
double * matrix_solve_gauss(double **, const int, const char * = 0);

void utworz(double **& T, const int n, const int m) {
	T = new double*[n];

	for (int i = 0; i < n; i++) {
		T[i] = new double[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			T[i][j] = 0;
		}
	}
}

void wypisz(double ** T, const int n, const int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(3) << T[i][j] << " ";
		}
		cout << endl << endl;
	}
}

void usun(double ** T, const int n) {
	if (T) {
		for (int i = 0; i < n; i++) {
			delete[] T[i];
		}
		delete[] T;
		T = 0;
	}
}

double * matrix_solve_gauss(double ** C, const int n, const char * file) {
	double * X = new double[n];

	for (int i = 0; i < n; i++) {
		X[i] = 0;
	}

	if (file) {
		ifstream plikMacierz(file);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				plikMacierz >> C[i][j];
			}
		}

		plikMacierz.close();
	}

	chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

	for (int s = 0; s < n - 1; s++) {
		for (int i = s + 1; i < n; i++) {
			for (int j = s + 1; j < n + 1; j++) {
				C[i][j] -= (C[i][s] / C[s][s]) * C[s][j];
			}
		}
	}

	X[n - 1] = C[n - 1][n] / C[n - 1][n - 1];

	for (int i = n - 2; i >= 0; i--) {
		double sum = 0;
		for (int s = i + 1; s < n; s++) {
			sum += (C[i][s] * X[s]);
		}
		X[i] = (C[i][n] - sum) / C[i][i];
	}

	chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();

	/*
	for (int i = 0; i < n; i++) {
		cout << X[i] << endl;
	}

	cout << endl << "Czas obliczenia ukladu rownan Gaussem: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

	delete [] X;
	X = 0;
	*/
	return X;
}



int main()
{
    double ** gauss_Matrix = 0;
    double * wynik = 0;
    unsigned n = 3;
	utworz(gauss_Matrix, n, n + 1);

	ifstream punkty("Punkty3.txt");
	for (int i = 0; i < n; i++) {
        int punktX = 0;
        punkty >> punktX;

        for (int j = 0; j < n; j++) {
            gauss_Matrix[i][j] = pow(punktX, j);
        }
        punkty >> gauss_Matrix[i][n];
	}

	punkty.close();
    wypisz(gauss_Matrix, n, n+1);
	wynik = matrix_solve_gauss(gauss_Matrix, n);
	cout << "Wielomian: ";
	ofstream wynikPlik("Wynik3.txt");
	for (int i = 0; i < n; i++) {
        wynikPlik << setprecision(12) << wynik[(n-1)-i] << "x^" << (n-1)-i << " + ";
	}
	wynikPlik.close();

	usun(gauss_Matrix, n);

	delete [] wynik;
	wynik = 0;
    return 0;
}
