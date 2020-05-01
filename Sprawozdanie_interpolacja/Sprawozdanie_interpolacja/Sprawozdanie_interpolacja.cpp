#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

char znak(double val) {
	return val > 0.0 ? '+' : '-';
}

int main()
{
	const int n = 10;
	int h = 1;

	double wyrazyWolne[n];
	double Punkty[n][2];
	double Pochodne[2][2] = { { 0, 1 }, { n-1, 1 } };

	ifstream punktyWejscie("Punkty10.txt");
	if (punktyWejscie.good()) {
		for (int i = 0; i < n; i++) {
			punktyWejscie >> Punkty[i][0];
			punktyWejscie >> Punkty[i][1];
		}

		punktyWejscie.close();

		wyrazyWolne[0] = (6 / h)*(((Punkty[1][1] - Punkty[0][1]) / h) - Pochodne[0][1]);

		for (int i = 1; i < n - 1; i++) {
			wyrazyWolne[i] = (6 / (h*h))*(Punkty[i - 1][1] - 2 * Punkty[i][1] + Punkty[i + 1][1]);
		}

		wyrazyWolne[n - 1] = (-6 / h) * ((Punkty[n - 1][1] - Punkty[n - 2][1]) / h - Pochodne[1][1]);

		double C[n][n + 1] = {};
		C[0][0] = 2;
		C[n - 1][n - 1] = 2;
		C[1][0] = 1;
		C[0][1] = 1;

		for (int i = 1; i < n - 1; i++) {
			C[i][i] = 4;
			C[i + 1][i] = 1;
			C[i][i + 1] = 1;
		}

		for (int i = 0; i < n; i++) {
			C[i][n] = wyrazyWolne[i];
		}

		double M[n]; // Wektor momentow

		for (int s = 0; s < n - 1; s++) {
			for (int i = s + 1; i < n; i++) {
				for (int j = s + 1; j < n + 1; j++) {
					C[i][j] -= (C[i][s] / C[s][s]) * C[s][j];
				}
			}
		}

		M[n - 1] = C[n - 1][n] / C[n - 1][n - 1];

		for (int i = n - 2; i >= 0; i--) {
			double sum = 0;
			for (int s = i + 1; s < n; s++) {
				sum += (C[i][s] * M[s]);
			}
			M[i] = (C[i][n] - sum) / C[i][i];
		}

		ofstream plikWyjsciowy("Punkty.txt");
		int k = 0;

		for (double x = 0; x <= n - 1; x += 0.01) {
			k = floor(x / 1) + 1;
			// Wygeneruj kolejne punkty do narysowania wykresu
			plikWyjsciowy << std::setfill('0') << std::setw(2) << std::fixed << x << "\t" << M[k - 1] * (pow(Punkty[k][0] - x, 3) / 6 * h) + M[k] * (pow(x - Punkty[k - 1][0], 3) / (6 * h)) + (Punkty[k - 1][1] - (M[k - 1] * h*h) / 6)*((Punkty[k][0] - x) / h) + (Punkty[k][1] - (M[k] * h*h) / 6)*(x - Punkty[k - 1][0]) / h << endl;
		}

		ofstream funkcjeSklejone("Sklejone.txt");
		for (int i = 1; i < n; i++) {
			k = i - 1;
			double a = (1.0 / 6.0 * h)*(M[i] - M[i - 1]);
			double b = (1.0 / 2.0) * (M[i - 1] * Punkty[i][0] - M[i] * Punkty[i - 1][0]);
			double c = (1.0 / 2.0 * h)*(M[i] * Punkty[i - 1][0] * Punkty[i - 1][0] - (M[i - 1] * Punkty[i][0] * Punkty[i][0])) + (h / 6.0)*(M[i - 1] - M[i]) + (1.0 / h)*(Punkty[i][1] - Punkty[i - 1][1]);
			double d = (1.0 / 6.0 * h)*(M[i - 1] * pow(Punkty[i][0], 3) - M[i] * pow(Punkty[i - 1][0], 3)) + (h / 6.0)*(M[i] * Punkty[i - 1][0] - M[i - 1] * Punkty[i][0]) + (1 / h)*(Punkty[i][0] * Punkty[i - 1][1] - Punkty[i - 1][0] * Punkty[i][1]);

			funkcjeSklejone << a << "*x^3" << ' ' << znak(b) << ' ' << fabs(b) << "*x^2" << ' ' << znak(c) << ' ' << fabs(c) << "*x" << ' ' << znak(d) << ' ' << fabs(d) << " Przedzial: [" << i - 1 << ", " << i << "]" << endl;
			double wartosc = a * pow(Punkty[k][0], 3) + b * pow(Punkty[k][0], 2) + c * Punkty[k][0] + d;
			cout << "X: " << Punkty[k][0] << " Y: " << Punkty[k][1] << endl;
			cout << "Wynik interpolacja: " << setprecision(16) << wartosc << endl;
			cout << "Blad procentowy: " << (fabs(Punkty[k][1] - wartosc) / fabs(Punkty[k][1])) * 100.0 << " %" << endl << endl;
			if (i == n - 1) {
				k = i;
				double wartosc = a * pow(Punkty[k][0], 3) + b * pow(Punkty[k][0], 2) + c * Punkty[k][0] + d;
				cout << "X: " << Punkty[k][0] << " Y: " << Punkty[k][1] << endl;
				cout << "Wynik interpolacja: " << setprecision(16) << wartosc << endl;
				cout << "Blad procentowy: " << (fabs(Punkty[k][1] - wartosc) / fabs(Punkty[k][1])) * 100.0 << " %" << endl << endl;
			}
		}
		funkcjeSklejone.close();
		plikWyjsciowy.close();
		system("pause");
	}

	return 0;
}
