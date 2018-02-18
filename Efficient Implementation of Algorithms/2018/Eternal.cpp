/*
Even if the world is full of counterfeits, I still regard it as wonderful.

Pile up herbs and incense, and arise again from the flames and ashes of its predecessor — as is known to many, the phoenix does it like this.

The phoenix has a rather long lifespan, and reincarnates itself once every a! years. Here a! denotes the factorial of integer a, that is, a! = 1 × 2 × ... × a. Specifically, 0! = 1.

Koyomi doesn't care much about this, but before he gets into another mess with oddities, he is interested in the number of times the phoenix will reincarnate in a timespan of b! years, that is, b!⁄a!. Note that when b ≥ a this value is always integer.

As the answer can be quite large, it would be enough for Koyomi just to know the last digit of the answer in decimal representation. And you're here to provide Koyomi with this knowledge.

Input
The first and only line of input contains two space-separated integers a and b (0 ≤ a ≤ b ≤ 1018).

Output
Output one line containing a single decimal digit — the last digit of the value that interests Koyomi.

Examples
Input:

2 4
Output:
2
Input:

0 10
Output:
0
Input:

107 109
Output:
2
Note
In the first example, the last digit of 4!⁄2! = 12 is 2;
In the second example, the last digit of 10!⁄0! = 3628800 is 0;
In the third example, the last digit of 109!⁄107! = 11772 is 2.

*/

#include <iostream>
#include <cstdio>

using namespace std;


int main(){


	long long a, b;
	scanf("%lld %lld", &a, &b);

	if(b < a || b - a >= 5) {
		printf("0\n");
		return 0;
	}

	int result = 1;

	for(int i = 1; i + a <= b; i++){
		result *= (a + i) % 10;
	}

	printf("%d\n", result % 10);

	return 0;
}