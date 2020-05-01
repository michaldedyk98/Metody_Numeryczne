#include <iostream>
#include <fstream>

using namespace std;

double **B;

void odwrotna(double ** B, const unsigned int n) {
    double c, d;

    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2*n; j++) {
            B[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
            B[i][n+i] = 1;
    }


    for (int s = 0; s < n; s++) {
        c = B[s][s];
        B[s][s] = B[s][s]-1.0;
        for ( int j = s+1; j < 2*n; j++) {
            d = B[s][j]/c;
            for ( int i = 0; i < n; i++) {
                B[i][j] = B[i][j] - (d*B[i][s]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2*n; j++) {
            cout << B[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    unsigned int n;

    cout << "Podaj rozmiar macierzy kwadratowej: ";
    cin >> n;

    B = new double*[n];

    for (int i = 0; i < n; i++) {
        B[i] = new double[2*n];
    }

    for (int i = 0; i < n; i++){
        for ( int j = 0; j < n; j++) {
            cout << "B[" << i << "][" << j << "] :";
            cin >> B[i][j];
        }
        cout << endl;
    }

    odwrotna(B, n);

    return 0;
}
