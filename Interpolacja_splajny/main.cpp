#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    const int n = 4;
    double wyrazyWolne[n];
    int h = 1;
    double punkty[n][2] = {{0, 1}, {1, 3}, {2, -1}, {3, 2}};
    double pochodne[2][2] = {{0, 1}, {0, 1}};

    wyrazyWolne[0] = (6/h)*(((punkty[1][1]-punkty[0][1])/h)-pochodne[0][1]);

    wyrazyWolne[1] = 6*(-1-2*3+1);
    wyrazyWolne[2] = 6*(2-2*-1+3);

    wyrazyWolne[3] = -6*((2+1)-1);

    double C[n][n+1] = {
        {2, 1, 0, 0},
        {1, 4, 1, 0},
        {0, 1, 4, 1},
        {0, 0, 1, 2}
    };

    C[0][4] = wyrazyWolne[0];
    C[1][4] = wyrazyWolne[1];
    C[2][4] = wyrazyWolne[2];
    C[3][4] = wyrazyWolne[3];

    double X[n];

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

	for (int i = 0; i < n; i++) {
		cout << X[i] << endl;
	}

	ofstream plikWyjsciowy("Punkty.txt");
	unsigned k = 0;

	for (double x = 0; x <= 3; x += 0.01) {
        if (x >=0 && x < 1) {
            //K = 1
            k = 1;
            plikWyjsciowy << std::setfill('0') << std::setw(2) << std::fixed << x << "\t" << X[k-1]*(pow(punkty[k][0]-x, 3)/6*h)+X[k]*(pow(x-punkty[k-1][0], 3)/(6*h))+(punkty[k-1][1]-(X[k-1]*h*h)/6)*((punkty[k][0]-x)/h)+(punkty[k][1]-(X[k]*h*h)/6)*(x-punkty[k-1][0])/h << endl;
        } else if (x >= 1 && x < 2) {
            //K = 2
            k = 2;
            plikWyjsciowy << std::setfill('0') << std::setw(2) << std::fixed << x << "\t" << X[k-1]*(pow(punkty[k][0]-x, 3)/6*h)+X[k]*(pow(x-punkty[k-1][0], 3)/(6*h))+(punkty[k-1][1]-(X[k-1]*h*h)/6)*((punkty[k][0]-x)/h)+(punkty[k][1]-(X[k]*h*h)/6)*(x-punkty[k-1][0])/h << endl;
        } else if(x >= 2 && x <= 3) {
            // K = 3
            k = 3;
            plikWyjsciowy << std::setfill('0') << std::setw(2) << std::fixed << x << "\t" << X[k-1]*(pow(punkty[k][0]-x, 3)/6*h)+X[k]*(pow(x-punkty[k-1][0], 3)/(6*h))+(punkty[k-1][1]-(X[k-1]*h*h)/6)*((punkty[k][0]-x)/h)+(punkty[k][1]-(X[k]*h*h)/6)*(x-punkty[k-1][0])/h << endl;

        }
	}

    return 0;
}
