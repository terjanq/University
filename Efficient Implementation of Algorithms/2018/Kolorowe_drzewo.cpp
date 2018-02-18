/*Bajtek ma drzewo o n wierzchołkach, a każdy z tych wierzchołków jest pokolorowany na jakiś kolor. Nie lubi jednak nieporządku, dlatego chciałby aby każde właściwe poddrzewo tego drzewa było w tym samym kolorze (przy czym dwa różne poddrzewa mogą mieć różne kolory). Czy jest w stanie powiesić to drzewo za pewien wierzchołek, tak aby mu się udało?

Wejście
W pierwszym wierszu wejścia dana jest liczba n (1 ≤ n ≤ 500 000) - liczba wierzchołków w drzewie. W kolejnych n-1 wierzchołkach dany jest opis krawędzi drzewa. W ostatnim wierszu dane jest n liczb - i-ta z nich oznacza kolor i-tego wierzchołka.

Wyjście
Należy wypisać jedno słowo: TAK lub NIE w zależności od tego, czy Bajtek może ukorzenić drzewo, tak aby spełnało warunki zadania.

Przykład
Dla danych wejściowych

6
1 4
1 2
1 3
4 5
5 6
1 1 1 3 2 2
poprawną odpowiedzią jest
TAK
*/
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 5e5 + 7;

vector<int> tree[N];
int colors[N];
bool visited[N];

int root_candidate1, root_candidate2;

bool correct = true;

void verify_subtree(int v, int c){
	visited[ v ] = true;
	if( c != colors[v] ) {
		correct = false;
		return ;
	}

	for(int i = 0; i < tree[v].size(); i++){
		if( !visited [ tree[v][i] ] )
			verify_subtree( tree[v][i], c );
	}
}


void find_candidates(int v){
	visited[ v ] = true;

	for(int i = 0; i < tree[v].size(); i++){
		if( !visited[ tree[ v ][ i ] ] ){
			if( colors[ v ] != colors[ tree[v][i] ] ){
				root_candidate1 = v;
				root_candidate2 = tree[v][i];
			}
			else{
				find_candidates( tree[v][i] );
			}
		}
	}
}

void clear_visited(int n){
	for(int i = 0; i <= n; i++){
		visited[ i ] = 0;
	}
}


int main(){
	int n, a, b;
	scanf("%d", &n);


	for(int i = 1; i < n; i++){
		scanf("%d %d", &a, &b);
		tree[ a ].push_back( b );
		tree[ b ].push_back( a );
	}

	int last_color = -1;
	int color_count = 1;

	for(int i = 1; i <= n; i++){
		scanf("%d", &colors[i]);
		if( last_color == -1 ) last_color = colors[ i ];
		else if( last_color != colors[ i ] ) {
			last_color = colors[ i ];
			color_count++;
		}
	}

	if(color_count == 1){
		printf("TAK\n");
		return 0;
	}

	find_candidates( 1 );

	clear_visited(n);
	visited[ root_candidate1 ] = true;

	for( int i = 0; i < tree[root_candidate1].size(); i++ ){
		verify_subtree( tree[root_candidate1][i], 
			colors[ tree[root_candidate1][i] ] );
	}

	if(correct){
		printf("TAK\n");
		return 0;
	}

	clear_visited(n);
	correct = true;

	visited[ root_candidate2 ] = true;

	for( int i = 0; i < tree[root_candidate2].size(); i++ ){
		verify_subtree( tree[root_candidate2][i], 
			colors[ tree[root_candidate2][i] ] );
	}

	if(correct){
		printf("TAK\n");
		return 0;
	}


	printf("NIE\n");

	return 0;
}