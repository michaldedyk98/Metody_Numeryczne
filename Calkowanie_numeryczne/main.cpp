#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double fnc(double x) {
    return 1 / x;
}

double calka_prostokat(double a, double b, unsigned n) {
    double dlugoscPrzedzialu = (b-a) / n;
    double * tab = new double[n];

    for (int i = 0; i < n; i++) {
        tab[i] = a + (i * dlugoscPrzedzialu);
    }
    double suma = 0.0;

    for (int i = 0; i < n; i++) {
        suma += fnc(tab[i]);
    }
    delete [] tab;

    return dlugoscPrzedzialu * suma;
}

double calka_trapez(double a, double b, unsigned n) {
    double dlugoscPrzedzialu = (b-a) / n;
    double * tab = new double[n];

    double suma = 0.0;

    for (int i = 0; i < n; i++) {
        tab[i] = a + (i * dlugoscPrzedzialu);
    }

    suma = (fnc(a) + fnc(b)) / 2;

    for (int i = 0; i < n; i++) {
        suma += fnc(tab[i]);
    }

    delete [] tab;

    return dlugoscPrzedzialu * suma;
}

double calka_simpsona(double a, double b, int n) {
    double dlugoscPrzedzialu = (b-a) / n;
    double calka = fnc(a) + fnc(b);
    double * x = new double[n];

    for (int i = 0; i < n; i++) {
        x[i] = a + i * dlugoscPrzedzialu;
    }

    for (int i = 1; i < n; i++) {
        if ( i % 2 ) calka += 4.0 * fnc(x[i]);
        else calka += 2.0 * fnc(x[i]);
    }

    delete [] x;

    return calka * dlugoscPrzedzialu/3.0;
}

int main()
{
    cout << "Wynik calka prostokatna: " << calka_prostokat(3,4, 10000) << endl;
    cout << "Wynik calka trapez: " << calka_trapez(3, 4, 10000) << endl;
    cout << "Wynik calka simpsona: " << calka_trapez(3, 4, 100000);

    return 0;
}
