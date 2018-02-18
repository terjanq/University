/*Mały Jaś poznał ostatnio grę Tetris. W grze tej klocki o różnych kształtach opadają na platformę. Gra ta zainspirowała Jasia do zastanowienia się nad następującym problemem. Załóżmy że wszystkie klocki to prostokąty o wymiarach (1, l), gdzie l to długość boku poziomego. Klocki mają opadać osobno, w pewnej ustalonej kolejności. Dany klocek opada, dopóki nie natrafi na przeszkodę w postaci platformy albo innego, już stojącego klocka, a wtedy się zatrzymuje (w pozycji, w jakiej opadał) i pozostaje na swoim miejscu do końca gry. Mając dane wymiary, kolejność opadania i tory lotu klocków gracz będzie musiał podać wysokość najwyżej położonego punktu w układzie powstałym po opadnięciu wszystkich klocków. Wszystkie klocki opadają pionowo w dół i nie obracają się w trakcie opadania.

Zadanie
Napisz program, który:

wczyta ze standardowego wejścia opisy kolejno opadających klocków,
wyznaczy najwyższy punkt układu klocków po zakończeniu ich opadania,
wypisze wynik na standardowe wyjście.
Wejście
W pierwszum wierszu wejścia znajdują się dwie liczby całkowite d, n (1 <= d <= 10^6, 1 <= n <= 2*10^4), oznaczające odpowiednio: szerokość platformy oraz liczbę klocków, które na nią opadną. W następnych n wierszach występują opisy kolejno opadających klocków. Każdy opis klocka składa się z dwóch liczb całkowitych: l, x (1 <= l <= d, 0 <= x, l+x <= d), reprezentujących klocek o szerokości l. Wierzchołki rzutu klocka na platformę będą miały współrzędne: x i x+l.

Wyjście
W jedynym wierszu wyjścia należy wypisać wysokość najwyższego punktu w układzie klocków po zakończeniu ich opadania.

Przykład
Dla danych wejściowych:

8 5
3 1
2 6
1 4
4 3
5 0
poprawną odpowiedzią jest:

3

Solution O(m*log(n) + n), interval_tree (interval, interval)
*/
#include <iostream>
#include <cstdio>

const int N = 1048576;
int tree_size = 1;

int interval_tree[2*N + 7];
int interval_tree_max[2*N + 7];

using namespace std;


void clear_tree(int k){
	tree_size = 1;
	while(tree_size < k) tree_size *= 2;

	for(int i = 0; i < 2*tree_size + 7; i++){
		interval_tree[i] = 0;
		interval_tree_max[i] = 0;
	}
}

int query_max(int a, int b){
	int va = tree_size + a, vb = tree_size + b;
	int maxval = max(interval_tree_max[ va ], interval_tree_max[ vb ]);

	while( va / 2 != vb / 2 ){
		if(va % 2 == 0)
			maxval = max(maxval, interval_tree_max[ va + 1 ]);
		if(vb % 2 == 1)
			maxval = max(maxval, interval_tree_max[ vb - 1 ]);
		va /= 2;
		vb /= 2;
		maxval = max(maxval, interval_tree[ va ]);
		maxval = max(maxval, interval_tree[ vb ]);
	}

	while( va / 2 > 0 ){
		va /= 2;
		maxval = max(maxval, interval_tree[ va ]);
	}

	return maxval;
}

void add(int a, int b){
	int va = tree_size + a, vb = tree_size + b;
	int val = query_max(a, b) + 1;

	interval_tree[ va ] = val;
	interval_tree[ vb ] = val;

	interval_tree_max[ va ] = val;
	interval_tree_max[ vb ] = val;

	while( va / 2 != vb / 2){
		if(va % 2 == 0) {
			interval_tree[ va + 1 ] = val;
			interval_tree_max[ va + 1 ] = val;
		}
		if(vb % 2 == 1) {
			interval_tree[ vb - 1 ] = val;
			interval_tree_max[ vb - 1 ] = val;
		}

		va /= 2;
		vb /= 2;

		interval_tree_max[ va ] = max(
			interval_tree_max[ 2 * va ],
			interval_tree_max[ 2 * va + 1 ]
			);

		interval_tree_max[ vb ] = max(
			interval_tree_max[ 2 * vb ], 
			interval_tree_max[ 2 * vb + 1]
			);

	}

	while( va / 2 > 0 ){
		va /= 2;
		interval_tree_max[ va ] = max(
			interval_tree_max[ 2 * va ],
			interval_tree_max[ 2 * va + 1 ]
			);
	}
}

void printTree(int tree[]){
	printf("### TREE ###\n");
	printf("%d", tree[1]);
	for(int i=2; i<2*tree_size; i++){
		if((i & (i-1)) == 0) printf("\n");
		printf("%d ", tree[i]);
	}

	printf("\n### \n");
}



int main(){

	int n, m, l, x;

	scanf("%d %d", &n, &m);

	clear_tree(n);

	while( m-- ){
		scanf("%d %d", &l, &x);
		add(x, x + l - 1);
	}

	// printTree(interval_tree);

	// printTree(interval_tree_max);

	printf("%d\n", query_max(0, n));
	return 0;
}