/*

It's normal to feel worried and tense the day before a programming contest. To relax, you went out for a drink with some friends in a nearby pub. To keep your mind sharp for the next day, you decided to play the following game. To start, your friends will give you a sequence of N integers X_1, X_2,..., X_n. Then, there will be K rounds; at each round, your friends will issue a command, which can be:

a change command, when your friends want to change one of the values in the sequence; or
a product command, when your friends give you two values I,J and ask you if the product X_I * X_{I+1} *...* X_J is positive, negative or zero.
Since you are at a pub, it was decided that the penalty for a wrong answer is to drink a pint of beer. You are worried this could a ect you negatively at the next day's contest, and you don't want to check if Ballmer's peak theory is correct. Fortunately, your friends gave you the right to use your notebook. Since you trust more your coding skills than your math, you decided to write a program to help you in the game.
Input
Each test case is described using several lines. The first line contains two integers N and K, indicating respectively the number of elements in the sequence and the number of rounds of the game (1 <= N, K <= 10^5). The second line contains N integers X_i that represent the initial values of the sequence (-100 <= X_i <= 100 for i = 1, 2,...,N). Each of the next K lines describes a command and starts with an uppercase letter that is either 'C' or 'P'. If the letter is `C', the line describes a change command, and the letter is followed by two integers I and V indicating that X_I must receive the value V (1 <= I <= N and -100 <= V <= 100). If the letter is `P', the line describes a product command, and the letter is followed by two integers I and J indicating that the product from X_I to X_J, inclusive must be calculated (1 <= I <= J <= N). Within each test case there is at least one product command.

Output
For each test case output a line with a string representing the result of all the product commands in the test case. The i-th character of the string represents the result of the i-th product command. If the result of the command is positive the character must be `+' (plus); if the result is negative the character must be `-' (minus); if the result is zero the character must be `0' (zero).

Example
Input

4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
5 9
1 5 -2 4 3
P 1 2
P 1 5
C 4 -5
P 1 5
P 4 5
C 3 0
P 1 5
C 4 -5
C 4 -5
Output 0+-
+-+-0


Solution: O(N + K*log(N)), interval_tree
*/

#include <iostream>
#include <cstdio>

const int N = 1048576;
int tree_size = 1;

int interval_tree[2*N + 7];


void clear_tree(int k){
	tree_size = 1;
	while(tree_size < k) tree_size *= 2;

	for(int i = 0; i < 2*tree_size + 7; i++){
		interval_tree[i] = 1;
	}
}

void add(int i, int val){
	int v = tree_size + i;

	if(val < 0) val = -1;
	else if(val > 0) val = 1;
	else val = 0;
	interval_tree[ v ] = val;

	while( v / 2 > 0){
		interval_tree[v / 2] = interval_tree[ v ];
		if(v % 2 == 0)
			interval_tree[ v / 2 ] *= interval_tree[ v + 1 ];
		else
			interval_tree[ v / 2 ] *= interval_tree[ v - 1 ];
		v /= 2;
	}
}

void printTree(){
	printf("### TREE ###\n");
	printf("%d", interval_tree[1]);
	for(int i=2; i<2*tree_size; i++){
		if((i & (i-1)) == 0) printf("\n");
		printf("%d ", interval_tree[i]);
	}

	printf("\n### \n");
}


int query(int a, int b){
	int va = tree_size + a, vb = tree_size + b;
	if(va == vb){
		return interval_tree [ va ];
	}

	int product = interval_tree[ va ] * interval_tree[ vb ];
	if(product == 0) return 0;

	while( va / 2 != vb / 2){
		if(va % 2 == 0) product *= interval_tree[ va + 1 ];
		if(vb % 2 == 1) product *= interval_tree[ vb - 1 ];
		va /= 2;
		vb /= 2;
	}

	return product;
}


char whatIs(int k){
	return k == 0 ? '0': k == 1 ? '+' : '-';
}
using namespace std;

int main(){

	int n, k;
	while(scanf("%d %d", &n, &k) != EOF){
		clear_tree(n);
		int temp1, temp2;
		char c;

		for(int i = 0; i < n; i++){
			scanf("%d", &temp1);
			add(i, temp1);
		}

		for(int i = 0; i < k; i++){
			scanf("\n%c %d %d", &c, &temp1, &temp2);
			if(c == 'C'){
				add(temp1 - 1, temp2);
			}
			else{
				printf("%c", whatIs(query(temp1 - 1, temp2 - 1)));
			}
		}
		printf("\n");
	}


	return 0;
}