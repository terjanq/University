/*
Jasio, jak każdy informatyk uwielbia cyfry 0 i 1. Lubi także liczby podzielne przez N. Chciałby połączyć te dwa zainteresowania i wymyślił zadanie.

Zadanie
Napisz program, który: wczyta liczbę N, wyznaczy najmniejszą dodatnią liczbę złożoną tylko z cyfr 0 i 1, która jest podzielna przez N i wypisze wynik na standardowe wyjście.

Wejście
W pierwszym i jedynym wierszu wejścia znajduje się jedna liczba naturalna N (1 <= N <= 10^6).

Wyjście
W pierwszym i jedynym wierszu wyjścia powinna się znaleźć jedna liczba całkowita - najmniejsza możliwa złożona tylko z cyfr 0 i 1, podzielna przez N.

Przykład
Dla danych wejściowych

7
poprawną odpowiedzią jest
1001

Solution < O(N),
Using theorem, that for every number n 
there is a a number consisted of 0s and 1s
divisible by n with number of digits <= n + 1.
I iterate over every comination, cutting the search tree
if a node was already proceeded. (BFS) 
        1
   10      11
100 101 110 111
...

And for each node I store its value modulo n instead of 
binary words.
*/


#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>

const int N = 1e6 + 7;

int hash_t[ N ];
using namespace std;

void printBin(int n){
	stack< char > st;
	int i = 0;
	
	while( i != 1 ){
		int j = hash_t[ i ];
		if(( j * 10 ) % n == i) st.push( '0' );
		else st.push( '1' );
		i = j;
	}

	st.push( '1' );
	while( !st.empty() ) {
		printf( "%c", st.top() );
		st.pop();
	}
}

int main(){

	int n;

	scanf("%d", &n);

	if(n == 1) {
		printf( "1\n" );
		return 0;
	}

	queue< int > q;
	q.push( 1 );

	while(! hash_t[0] ){
		int t = q.front();
		q.pop();

		int t1 = ( t * 10 ) % n;
		int t2 = (t * 10 + 1) % n;
		if( !hash_t[t1] ) {
			q.push( t1 );
			hash_t[ t1 ] = t;
		}
		if(!hash_t[ t2 ]){
			q.push( t2 );
			hash_t[ t2 ] = t;
		}
	}

	printBin( n );

	return 0;
}