#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double funkcja_wielomianowa(double x) {
	return pow(x, 5) + ((1.0/6.0) * pow(x, 4)) + 4 * pow(x, 3) - x*x - 6 * x + 4;
}

double funkcja_liniowa(double x) {
	return 4*x + 6;
}

double funkcja_kwadratowa(double x) {
	return 12*x*x + 3*x + 5;
}

double calka_prostokat(double (*funkcja)(double), double a, double b, unsigned n) {
	if (n == 0) return 0.0;

	double dlugoscPodprzedzialu = (b - a) / n;
	double suma = 0.0;

	for (int i = 1; i <= n; i++) {
		suma += funkcja(a + i * dlugoscPodprzedzialu);
	}

	return dlugoscPodprzedzialu * suma;
}

double calka_trapez(double(*funkcja)(double), double a, double b, unsigned n) {
	if (n == 0) return 0.0;

	double dlugoscPodprzedzialu = (b - a) / n;
	double suma = (funkcja(a) + funkcja(b)) / 2.0;

	for (int i = 1; i < n; i++) {
		suma += funkcja(a + i * dlugoscPodprzedzialu);
	}

	return dlugoscPodprzedzialu * suma;
}

double calka_simpsona(double(*funkcja)(double), double a, double b, int n) {
	if (n == 0) return 0.0;

	double dlugoscPodprzedzialu = (b - a) / (double)n;
	double suma = funkcja(a) + funkcja(b);

	for (int i = 1; i < n; i++) {
		double xi = a + i * dlugoscPodprzedzialu;

		if (i % 2) suma += 4.0 * funkcja(xi);
		else suma += 2.0 * funkcja(xi);
	}

	return suma * (dlugoscPodprzedzialu / 3.0);
}

int main()
{
	cout << "Funkcja liniowa - wynik metoda prostokatow: " << setprecision(6) << calka_prostokat(funkcja_liniowa, 0, 2, 100) << endl;
	cout << "Funkcja liniowa - wynik metoda trapezow: " << setprecision(6) << calka_trapez(funkcja_liniowa, 0, 2, 1) << endl;
	cout << "Funkcja liniowa - wynik metoda Simpsona: " << setprecision(6) << calka_simpsona(funkcja_liniowa, 0, 2, 2) << endl << endl;

	cout << "Funkcja kwadratowa - wynik metoda prostokatow: " << setprecision(6) << calka_prostokat(funkcja_kwadratowa, 0, 4, 100) << endl;
	cout << "Funkcja kwadratowa - wynik metoda trapezow: " << setprecision(6) << calka_trapez(funkcja_kwadratowa, 0, 4, 100) << endl;
	cout << "Funkcja kwadratowa - wynik metoda Simpsona: " << setprecision(6) << calka_simpsona(funkcja_kwadratowa, 0, 4, 2) << endl << endl;

	cout << "Funkcja wielomianowa - wynik metoda prostokatow: " << setprecision(6) << calka_prostokat(funkcja_wielomianowa, -1, 1, 100) << endl;
	cout << "Funkcja wielomianowa - wynik metoda trapezow: " << setprecision(6) << calka_trapez(funkcja_wielomianowa, -1, 1, 100) << endl;
	cout << "Funkcja wielomianowa - wynik metoda Simpsona: " << setprecision(6) << calka_simpsona(funkcja_wielomianowa, -1, 1, 20) << endl;

	system("pause");

	return 0;
}
