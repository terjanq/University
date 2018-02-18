/*
Ada loves to cook for her friends. Her pantry has room for P different ingredients (each labelled from 0 to P-1). At the moment, she only has M of the P ingredients on hand. Because Ada is a programmer, she represents her cookbook as a matrix M where a cell Mi,j = 0 or 1 describes if a recipe number i needs an ingredient number j.

Ada wants to prepare N different dishes. If she doesn't have a certain ingredient in her pantry, she must purchase it; however, once she has an ingredient, she can use it in all recipes. Ada keeps a record of all ingredient costs in an array C where Ci is the cost of purchasing pantry ingredient number j.

Find the minimum cost for Ada to cook N different recipes and print it on a new line.

Input
The first line contains an integer Q (1≤Q≤20) – the number of queries. The subsequent lines describe each query in the following format: the first line of the query contains R (1≤R≤30) - the number of recipes, P (1≤P≤13) - the number of different ingredients, N (1≤N≤min(10,R)) - the number of dishes to prepare, and M (1≤M≤P) - the number of ingredients Ada has in her pantry.

The next line contains M integers describing ingredients present in Ada's pantry. The third line contains P integers describing cost array C (1≤Ci≤104). At the end, there is a binary matrix M of size R x P describing the necessity of ingredients in each recipe.

Output
For each query, print an integer on a new line denoting the minimum cost to prepare N dishes.

Example
Input:

1
4 5 2 2
3 4
1 3 2 4 8
0 0 1 0 0
1 1 1 1 1
1 0 0 0 1
1 1 0 1 1
Output:
3

Solution: O(Q * 2^P * R)
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_INT = 1e9;
const int PP = 17;
const int RR = 33;
int min_cost = MAX_INT;

void recursive_solution(int i, int I, int M[][PP], const int &R, const int &P, int curr_cost, const int costs[], const int &N) {

	int count = 0;
	for(int r = 0; r < R; r++){
		if( M[ r ][ i ] ){
			M[ r ][ P ]--;
		}
		if( M[ r ][ P ] <= 0) count++;
	}

	if( count >= N ) {
		min_cost = min( curr_cost, min_cost );
	}

	if(I > 0){
		for(int j = i + 1; j < P; j++)
			if( costs[j] )
			recursive_solution(j, I - 1, M, R, P, curr_cost + costs[j], costs, N);
	}

	for(int r = 0; r < R; r++){
		if( M[ r ][ i ] ){
			M[ r ][ P ]++;
			if( M[ r ][ P ] <= 0) count++;
		}
	}

}


int main(){
	
   int Q;
   scanf("%d", &Q);

	while(Q--){
		min_cost = MAX_INT;
	   	int R, P, N, m;
	   	int she_has[PP];
	   	int costs[PP];
	   	int M[RR][PP];

	   	scanf("%d %d %d %d", &R, &P, &N, &m);
	   	

	   	for(int i = 0; i < m; i++) scanf("%d", &she_has[i]);
	   	for(int i = 0; i < P; i++) scanf("%d", &costs[i]);

	   	int I = 0;

	   	for(int r = 0; r < R; r++){
	   		M[r][P] = 0;
	   		for(int p = 0; p < P; p++)
	   			scanf("%d", &M[r][p]);
	   	}

	   	for(int i = 0; i < m; i++){
	   		int p = she_has[i];
	   		costs[p] = 0;
	   		for(int r = 0; r < R; r++)
	   			M[r][p] = 0;
	   	}

	   	for(int r = 0; r < R; r++)
	   		for(int p = 0; p < P; p++){
	   			if( M[r][p] ) {
	   				M[r][P]++;
	   				M[r][p] = costs[p];
	   			}
	   		}

	   	int count = 0;
		for(int r = 0; r < R; r++){
			if( M[ r ][ P ] <= 0) count++;
		}

		if(count >= N){
			min_cost = 0;
		}
		else{
			for(int l = 0; l < P; l++){
				for(int i = 0; i < P; i++){
					if( costs[i] )
						recursive_solution(i, l, M, R, P, costs[i], costs, N);
				}
		   	}
		}
	   	printf("%d\n", min_cost);
	}

	return 0;
}