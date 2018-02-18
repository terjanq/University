/*
Bessie likes downloading games to play on her cell phone, even though she does find the small touch screen rather cumbersome to use with her large hooves.

She is particularly intrigued by the current game she is playing. The game starts with a sequence of N positive integers (2 ≤ N ≤ 262144), each in the range 1…40. In one move, Bessie can take two adjacent numbers with equal values and replace them a single number of value one greater (e.g., she might replace two adjacent 7s with an 8). The goal is to maximize the value of the largest number present in the sequence at the end of the game. Please help Bessie score as highly as possible!

Input
The first line of input contains N, and the next N lines give the sequence of N numbers at the start of the game.

Output
Please output the largest integer Bessie can generate.

Example
input

4
1
1
1
2
output
3

*/

#include <iostream>
#include <cstdio>

using namespace std;

const int N = 300000;
const int maxP = 80;

int arr[N];
int dp[maxP][N];

int main(){

	int n, result = 0;

	scanf("%d", &n);

	for(int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
		result = max(result, arr[i]);
	}

	for(int p = 1; p < maxP; p++){
		for(int i = 1; i <= n; i++){
			if( arr[i] == p ){
				dp[p][i] = i + 1;	
			}
			else{
				if( dp[p - 1][i] && dp[p - 1][i] <= n && dp[p - 1][ dp[p - 1][i] ]) 
					result = max(result, p);
				dp[p][i] = dp[p - 1][ dp[p - 1][i] ];
			
			}
		}
	}

	printf("%d\n", result);

	return 0;
}