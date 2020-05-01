#include <iostream>
#include <cmath>
#include <iomanip>

#define M_PI 3.141592653589793238

using namespace std;

double fnc(double x) {
    return 7*x-x*x;
}

int main()
{
    const int n = 3;
    const int wezly = n*2+1;

    double Macierz[wezly][wezly] = {};
    double MacierzTrans[wezly][wezly] = {};
    double Wyniki[wezly];
    double X[wezly], Y[wezly];

    for (int i = 0; i < wezly; i++) {
        X[i] = (2 * i * M_PI) / (2 * n + 1);
        Y[i] = fnc(X[i]);
    }

    for (int i = 0; i < wezly; i++) {
        Macierz[i][0] = 1 / sqrt(2.0);
    }

    double mnoznik = 0.0;
    for (int i = 0; i < wezly; i++) {
        for (int j = 1; j < wezly; j++) {
            mnoznik = floor(((j-1)/2)+1);

            if (j % 2) {
                Macierz[i][j] = sin(mnoznik * X[i]);
            } else {
                Macierz[i][j] = cos(mnoznik * X[i]);
            }
        }
        cout << endl;
    }

    for (int i = 0; i < wezly; i++) {
        for (int j = 0; j < wezly; j++) {
            MacierzTrans[i][j] = Macierz[j][i];
        }
    }

    //Odwroc
    for (int i = 0; i < wezly; i++) {
        for (int j = 0; j < wezly; j++) {
            MacierzTrans[i][j] *= 2.0 / wezly;
        }
    }

    double sum = 0.0;

    for (int i = 0; i < wezly; i++) {
        sum = 0.0;
        for (int s = 0; s < wezly; s++) {
            sum += MacierzTrans[i][s] * Y[s];
        }

        Wyniki[i] = sum;
    }


    for (int i = 0; i < wezly; i++) {
        cout << Wyniki[i] << endl;
    }

    return 0;
}
