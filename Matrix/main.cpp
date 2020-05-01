// Macierze_Operacje.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <Windows.h>

using namespace std;

void wypisz(double ** T, const int n, const int m);
void utworz(double **& T, const int n, const int m);
void usun(double ** T, const int n);
void matrix_solve_gauss(double **, const int, const char * = 0);
double ** matrix_mul(double **, const int, const int, double **, const int, const int, const char * = 0, const char * = 0);
double matrix_det(double **, const int, const char * = 0);
double ** matrix_inv(double **, const int, const char * = 0);

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

void matrix_solve_gauss(double ** C, const int n, const char * file) {
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

	for (int i = 0; i < n; i++) {
		cout << X[i] << endl;
	}

	cout << endl << "Czas obliczenia ukladu rownan Gaussem: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

	delete [] X;
	X = 0;
}

double ** matrix_mul(double **A, const int n, const int m, double ** B, const int x, const int y, const char * streamA, const char * streamB) {
	if (m == x) {
		double ** C = 0;
		utworz(C, n, y);

		if (!(streamA && streamB)) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					A[i][j] = rand() % 20;
				}
			}

			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					B[i][j] = rand() % 20;
				}
			}
		}
		else {
			ifstream macierzA(streamA);
			ifstream macierzB(streamB);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					macierzA >> A[i][j];
				}
			}

			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					macierzB >> B[i][j];
				}
			}

			macierzA.close();
			macierzB.close();
		}

		double sum = 0;

		chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < y; j++) {
				sum = 0;
				for (int s = 0; s < m; s++) {
					sum += A[i][s] * B[s][j];
				}
				C[i][j] = sum;
			}
		}

		chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();

		cout << endl << "Czas obliczenia ukladu rownan Gaussem: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;

		return C;
	} else cout << "Nie mozna wymnozyc macierzy, liczba kolumn macierzy A jest rozna od liczby wierszy macierzy B" << endl;

	return 0;
}

double matrix_det(double ** A, const int n, const char * file) {
	double det = 0;
	double ** B = 0;
	double ** A_copy = 0;
	utworz(B, n, n);
	utworz(A_copy, n, n);

	if (file) {
		ifstream plikMacierz(file);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {

				plikMacierz >> A_copy[i][j];
			}
		}
		plikMacierz.close();
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A_copy[i][j] = A[i][j];
			}
		}
	}

	det = A_copy[0][0];

	for (int s = 0; s < n - 1; s++) {
		for (int j = s + 1; j < n; j++) {
			B[s][j] = A_copy[s][j] / A_copy[s][s];
		}
		for (int i = s + 1; i < n; i++) {
			for (int j = s + 1; j < n; j++) {
				A_copy[i][j] -= A_copy[i][s] * B[s][j];
			}
		}
		det *= A_copy[s + 1][s + 1];
	}

	usun(A_copy, n);
	usun(B, n);

	return det;
}

double ** matrix_inv(double ** B, const int n, const char * file) {
	double c, d;
	double ** m_inv = 0;
	double ** A = 0;
	utworz(A, n, 2*n);

	if (file) {
		ifstream plikMacierz(file);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {

				plikMacierz >> A[i][j];
			}
		}
		plikMacierz.close();
	} else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j] = B[i][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		A[i][n + i] = 1;
	}


	for (int s = 0; s < n; s++) {
		c = A[s][s];
		A[s][s] = A[s][s] - 1.0;
		for (int j = s + 1; j < 2 * n; j++) {
			d = A[s][j] / c;
			for (int i = 0; i < n; i++) {
				A[i][j] = A[i][j] - (d*A[i][s]);
			}
		}
	}

	utworz(m_inv, n, n);

	for (int i = 0; i < n; i++) {
		for (int j = n; j < 2 * n; j++) {
			m_inv[i][j - n] = A[i][j];
		}
	}

	usun(A, n);

	return m_inv;
}

void stworzMacierzTestowa(const char * tekst, const int n, const int m) {
	ofstream macierzTestowa;
	macierzTestowa.open(tekst);

	if (macierzTestowa) {
		std::chrono::time_point<std::chrono::steady_clock> start = chrono::steady_clock::now();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				macierzTestowa << rand() % 40 << " ";
			}
		}

		std::chrono::time_point<std::chrono::steady_clock> end = chrono::steady_clock::now();

		cout << endl << "Czas utworzenia i zapisania macierzy: " << chrono::duration_cast<chrono::seconds>(end - start).count() << endl;
	}

	macierzTestowa.close();
}

void macierz_trojdiagonalna(double *a, double *b, double *c, double *d, double ) {
}

int main()
{
	//double ** gauss_Matrix = 0;
	//double ** mul_A = 0;
	//double ** mul_B = 0;
	//double ** mul_C = 0;
	//double ** macierz_odwrotna = 0;

	//stworzMacierzTestowa("gauss_test.txt", 2000, 2001);

	//cout << "Podaj rozmiar tablicy: " << endl;
	//cin >> n;

	//Rozwiazywanie ukladu rownan gaussem
	unsigned n = 6;
	utworz(gauss_Matrix, n, n + 1);

	ifstream punkty("Punkty.txt");
	for (int i = 0; i < n; i++) {
        int punktX;


        for (int j = 0; j < n; i++) {

        }
	}

	matrix_solve_gauss(gauss_Matrix, n, "Punkty.txt");
	usun(gauss_Matrix, n);
	//-------------------------------

	//Mnozenie macierzy
	//int A_r = 300, A_c = 300;
	//int B_r = 300, B_c = 300;

	//utworz(mul_A, A_r, A_c);
	//utworz(mul_B, B_r, B_c);
	//mul_C = matrix_mul(mul_A, A_r, A_c, mul_B, B_r, B_c);
	//wypisz(mul_C, A_r, B_c);
	//usun(mul_A, A_r);
	//usun(mul_B, B_r);
	//double wyznacznik = matrix_det(mul_C, A_r);
	//cout << "Wyznacznik wynosi: " << wyznacznik << endl;

	//macierz_odwrotna = matrix_inv(mul_C, A_r);

	//wypisz(macierz_odwrotna, A_r, A_r);
	//-------------------------------

	system("pause");

	return 0;
}
