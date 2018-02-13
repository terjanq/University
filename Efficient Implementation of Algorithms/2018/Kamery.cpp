/*Zadanie
Przy Twojej ulicy znajduje się n domów, ponumerowanych kolejno liczbami od 1 od n. Na k spośród tych domów zainstalowano kamery monitoringu. Straż obywatelska, świadoma tego, że nie wszystkie domy objęte są monitoringiem, chciałaby zainstalować dodatkowe kamery, tak by wśród każdych r kolejnych domów co najmniej 2 miały zainstalowane kamery.

Jaka jest minimalna liczba kamer, które trzeba dodatkowo zainstalować?

Wejście
Pierwszy wiersz wejścia zawiera trzy liczby naturalne: n (2 ≤ n ≤ 100000), k (0 ≤ k ≤ n), oraz r (2 ≤ r ≤ n).

Każdy z k następnych wierszy zawiera lokalizację jednej kamery (tj. numer domu, na którym zainstalowana jest kamera).

Wyjście
W jedynym wierszu wyjścia wypisz jedną liczbę naturalną, równą minimalnej liczbie kamer, które trzeba dodatkowo zainstalować.
	
Przykład
Dla danych wejściowych

15 5 4
2
5
7
10
13
poprawną odpowiedzią jest
3

22.12.2018
O(n + k + r)
*/

#include <iostream>
#include <cstdio>

using namespace std;

const int N = 100007;
const int M = 2; // minimal value of cams
int cams[N];

int main(){

	int n, k, r;

	scanf("%d%d%d", &n, &k, &r);

	for(int i = 0; i < k; i++){
		int cam;
		scanf("%d", &cam);
		cams[cam] = 1;
	}

	int curr_cams = 0, to_install = 0;

	for(int i = 0; i < r; i++){
		curr_cams += cams[i];
	}

	if(curr_cams < M) to_install = M - curr_cams;

	int temp_counter = to_install;

	for(int i = r - 1; temp_counter; i--){
		if(!cams[i]) {
			cams[i] = 1;
			temp_counter--;
			curr_cams++;
		}
	}

	for(int i = r; i < n; i++){
		curr_cams -= cams[ i - r];
		curr_cams += cams[ i ];
		if(curr_cams < M) {
			to_install++;
			curr_cams++;
			cams[i] = 1;
		}
	}

	printf("%d\n", to_install);

	return 0;
}