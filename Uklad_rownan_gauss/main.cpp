#include <iostream>
#include <fstream>

using namespace std;

void wypisz(double ** T, const unsigned int n);
void matrix_gauss(double ** C, const unsigned int n);
void matrix_mul(double ** n, double ** m, double ** k);

void matrix_gauss(double ** C, const unsigned int n) {
    double * X = new double[n];

    for ( int i = 0; i < n; i++) {
        X[i] = 0;
    }

    ifstream plikMacierz("Macierz.txt");

    cout << "Podaj wartosci macierzy glownej: " << endl;
    for ( int i = 0; i < n; i++) {
        for ( int j = 0; j < n+1; j++) {
            //cout << "C[" << i << "][" << j << "] : ";
            plikMacierz >> C[i][j];
        }
       // cout << endl;
    }

    plikMacierz.close();

    for( int s = 0; s < n - 1; s++) {
        for ( int i = s + 1; i < n; i++) {
            for ( int j = s + 1; j < n + 1; j++) {
                C[i][j] -= (C[i][s] / C[s][s]) * C[s][j];
            }
        }
    }

    X[n - 1] = C[n-1][n] / C[n-1][n-1];

    for ( int i = n - 2; i >= 0; i--) {
        double sum = 0;
        for ( int s = i + 1; s < n; s++) {
            sum += (C[i][s] * X[s]);
        }
        X[i] = (C[i][n] - sum) / C[i][i];
    }

    cout << endl;

    for (int i = 0; i < n; i++ ) {
        cout << X[i] << endl;
    }

    delete [] X;
    X = 0;
}

void matrix_mul(double ** n, double ** m, double ** k) {

}

void utworz(double **& T, const unsigned int n, const unsigned int m) {
    T = new double*[n];

    for ( int i = 0; i < m; i++) {
        T[i] = new double[n];
    }

    for ( int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            T[i][j] = 0;
        }
    }
}

void wypisz(double ** T, const unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n+1; j++) {
            cout << T[i][j] << "\t";
        }
        cout << endl;
    }
}

void usun(double ** T, const unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        delete [] T[i];
    }
    delete [] T;
    T = 0;
}

int main()
{
    unsigned int n;
    double ** C = 0;

    cout << "Podaj rozmiar tablicy: " << endl;
    cin >> n;

    utworz(C, n, n+1);
    matrix_gauss(C, n);
    usun(C, n);

    return 0;
}
