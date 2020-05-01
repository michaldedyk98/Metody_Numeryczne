#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

double wyz;

double **A;
double **B;

int main()
{
    unsigned int n;

    cout << "Podaj rozmiar macierzy kwadratowej: ";
    cin >> n;

    A = new double*[n];
    B = new double*[n];

    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        B[i] = new double[n];
    }

    ifstream plikMacierz("Macierz.txt");

    for (int i = 0; i < n; i++ ) {
        for (int j = 0; j < n; j++) {
            //A[i][j] = rand() % 10;
            //cout << "A[" << i << "][" << j << "] :";
            //cin >> A[i][j];

            plikMacierz >> A[i][j];
        }
    }
    plikMacierz.close();

    wyz = A[0][0];

    for (int s = 0; s < n-1; s++) {
        for (int j = s + 1; j < n; j++) {
            B[s][j] = A[s][j] / A[s][s];
        }
        for (int i = s + 1; i < n; i++) {
            for(int j = s + 1; j < n; j++) {
                A[i][j] -= A[i][s]*B[s][j];
            }
        }
        wyz *= A[s+1][s+1];
    }

    cout << "Wyznacznik wynosi: " << wyz << endl;

    for (int i = 0; i < n; i++) {
        delete [] A[i];
        delete [] B[i];
    }

    delete [] A;
    delete [] B;

    return 0;
}
