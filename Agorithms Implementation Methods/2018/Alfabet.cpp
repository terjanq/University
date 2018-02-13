/*
Zadanie
Słowo złożone z małych liter alfabetu angielskiego nazywamy alfabetycznym, jeśli po usunięciu pewnej liczby (być może zero) jego liter możemy otrzymać słowo "abcdefghijklmnopqrstuvwxyz".

Dla danego słowa s oblicz, jaka jest minimalna liczba liter, których wstawienie do słowa s uczyni je alfabetycznym.

Wejście
W jedynym wierszu wejścia znajduje się słowo s (1≤|s|≤50), złożone z małych liter alfabetu angielskiego.

Wyjście
W jedynym wierszu wyjścia wypisz jedną liczbę całkowitą, równą minimalnej liczbie liter, które trzeba wstawić do słowa s, by uczynić je alfabetycznym.


12.02.2018
O(s^2)
*/

#include <iostream>


using namespace std;

int main(){
	ios_base::sync_with_stdio(0);

	const int N = 57;

	string s;
	cin >> s;
	int n = s.size();
	int dp[N];
	int maximum_dp = 1;

	dp[n - 1] = 1;
	for(int i = n - 2; i >= 0; i--){
		dp[ i ] = 1;
		for(int j = i + 1; j < n; j++){
			if(s[i] < s[j]) dp[ i ] = max(dp[ i ], dp [ j ] + 1);
		}
		maximum_dp = max(maximum_dp, dp[ i ]);
	}


	cout << (26 - maximum_dp) << "\n";

	return 0;
}