/*
A number is perfect if it is equal to the sum of its divisors, the ones that are smaller than it. For example, number 28 is perfect because 28 = 1 + 2 + 4 + 7 + 14. Motivated by this definition, we introduce the metric of imperfection of number N, denoted with f(N), as the absolute difference between N and the sum of its divisors less than N. It follows that perfect numbers’ imperfection score is 0, and the rest of natural numbers have a higher imperfection score. For example:

f(6) = |6 - 1 - 2 - 3| = 0
f(11) = |11 - 1| = 10
f(24) = |24 - 1 - 2 - 3 - 4 - 6 - 8 - 12| = |-12| = 12
Write a programme that, for positive integers A and B, calculates the sum of imperfections of all numbers between A and B: f(A) + f(A + 1) + ... + f(B).

Input
The first line of input contains the positive integers A and B (1 <= A <= B <= 10^6). ​

Output
The first and only line of output must contain the required sum.

12.02.2018
O*(B * log(B))
*/

#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;


int main(){

int A, B;
scanf("%d%d", &A, &B);

int dp[ B + 1 ];
dp[0] = 0;
dp[1] = 1;

for(int i = 2; i <= B; i++) dp[ i ]= i - 1;

for(int i = 2; i <= B; i++){
	for(int j = 2; i * j <= B; j++){
		dp[ i * j ] -= i;
	}
}


long long result = 0;
for(int i = A; i <= B; i++)
	result += abs(dp[i]);


printf("%Ld", result);

return 0;
}