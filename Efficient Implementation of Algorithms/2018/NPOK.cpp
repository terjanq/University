/*Zadanie
Oblicz ( n k ) mod p.

Wejście
Pierwszy wiersz wejścia zawiera liczbę testów t (1 <= t <= 100). W każdym kolejnym wierszu podane są trzy liczby całkowite n, k i p (0 <= k <= n <= 106; n < p <= 109+7). Liczba p jest pierwsza.

Wyjście
Dla każdego testu wypisz ( n k ) mod p.

Przykład
Dla danych wejściowych

3 
4 2 5
7 1 11
2000 1000 1000000007
poprawną odpowiedzią jest
1
7
72475738


Soultion: O(n*t)

*/

#include <iostream>
#include <cstdio>


using namespace std;

int fast_pow(long long a, long long n, int M){
	if( n == 0 ) return 1;
	if( n == 1 ) return a;

	if( n % 2 == 0 ) 
		return fast_pow( (a * a) % M, n / 2, M);
	return (a * fast_pow(a, n - 1, M)) % M;
}

const int N = 1e6 + 7;

long long factorials[N];


int main(){
	int T;

	int n, k, p;

	factorials[0] = 1;

	scanf("%d", &T);


	while(T--){
		scanf("%d %d %d", &n, &k, &p);

		k = min(n - k, k);
		for(int i=1; i<=n; i++)
			factorials[i] = (factorials[ i - 1 ] * i ) % p;

		long long result = factorials[ n ] * fast_pow( factorials[ n - k ], p - 2, p);

		result %= p;

		result *= fast_pow(factorials[ k ], p - 2, p);
		result %= p;

		printf("%d\n", (int)result);
	}
	return 0;
}