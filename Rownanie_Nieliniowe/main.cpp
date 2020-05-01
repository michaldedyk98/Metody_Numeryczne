#include <iostream>
#include <cmath>

using namespace std;

void bisekcja() {
    /*
    long double a, b, x1, x2, x;
    long double eps = 1e-30;

    cout << "Podaj a, b: ";

    cin >> a >> b;

    x1 = a;
    x2 = b;

    if (fnc(a) * fnc(b) < 0) {
        for (long long int i = 0; ; i++) {
            x = (x1+x2) / 2;
            long double y = fnc(x);
            long double y1 = fnc(x1);

            if (y * y1 > 0) {
                x1 = x;
            } else {
                x2 = x;
            }

            if (abs(fnc(x)) < eps) {
                cout << "Liczba iteracji: " << i << endl;
                break;
            }
        }

        cout << x;
    } else cout << "Podany przedzial jest nieprawidlowy brak miejsc zerowych.";
    */
}

void sieczne() {
    /*
        int n = 0;
    double a, b, xk;
    double * x = 0;

    cout << "Podaj a, b, n, xk: ";

    cin >> a >> b >> n >> xk;

    if (n > 0) {
        x = new double[n];
        for (int i = 0; i < n; i++) {
            x[i] = 0;
        }
    }

    if (fnc(a) * fnc(b) < 0) {
        if (xk == a) x[0] = b;
        else x[0] = a;

        for (int i = 1; i < n; i++) {
            x[i] = x[i-1]-fnc(x[i-1])*((xk-x[i-1])/((fnc(xk) - fnc(x[i-1]))));
        }

        cout << x[n-1];
    } else cout << "Brak miejsc zerowych."

    delete [] x;
    */
}

long double fnc(long double x) {
    return x*x - 4;
}

long double pochodna(long double x) {
    return 2 * x;
}

int main()
{
    int n;
    double a, b;
    double eps = 1e-3;
    double * x = 0;

    cout << "Podaj a, b, n, x[0]: ";

    cin >> a >> b >> n;

    if (fnc(a) * fnc(b) < 0) {
        if (n > 0) {
            x = new double[n];
            for (int i = 0; i < n; i++) {
                x[i] = 0;
            }
        }

        cin >> x[0];

        for (int i = 1; i < n; i++) {
            x[i] = x[i-1] - fnc(x[i-1]) / pochodna(x[i-1]);
            if (abs(fnc(x[i])) < eps) {
                cout << x[i] << endl;
                cout << "liczba iteracji petli: " << i << endl;

                break;
            }
        }
    }
    delete [] x;

    return 0;
}
