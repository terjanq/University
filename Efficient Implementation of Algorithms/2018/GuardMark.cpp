/*Farmer John and his herd are playing frisbee. Bessie throws the frisbee down the field, but it's going straight to Mark the field hand on the other team! Mark has height H (1 <= H <= 1,000,000,000), but there are N cows on Bessie's team gathered around Mark (2 <= N <= 20). They can only catch the frisbee if they can stack up to be at least as high as Mark. Each of the N cows has a height, weight, and strength. A cow's strength indicates the maximum amount of total weight of the cows that can be stacked above her. Given these constraints, Bessie wants to know if it is possible for her team to build a tall enough stack to catch the frisbee, and if so, what is the maximum safety factor of such a stack. The safety factor of a stack is the amount of weight that can be added to the top of the stack without exceeding any cow's strength.

Input
The first line of input contains N and H. The next N lines of input each describe a cow, giving its height, weight, and strength. All are positive integers at most 1 billion.

Output
If Bessie's team can build a stack tall enough to catch the frisbee, please output the maximum achievable safety factor for such a stack. Otherwise output "Mark is too tall" (without the quotes).

Example
For input

4 10
9 4 1
3 3 5
5 5 10
4 4 5
the correct answer is
2

Soultion: << O(2^n). I'm using the observation, that if cow_i has its sum
of weight and strength bigger than cow_j, then it's more optimal that
cow_i is below cow_j and with this observation I am searching over all 
possible subsets of sorted array of cows (by putting cow at the top of the 
stack, or skipping) with using backtracking.

*/

#include <iostream>
#include <algorithm>
#include <cstdio>



using namespace std;

int N;
long long H;

long long heights[ 20 ];
long long weights[ 20 ];
long long strengths[ 20 ];
long long indicies [ 20 ];

long long safetyFactor = (1 << 31) - 1;
long long total_h = 0;

long long answer = -1;


void dfs(int i){
    if(i == N) return;

    long long cow = indicies[i];

    if( safetyFactor >= weights[cow] ){
        long long oldSafety = safetyFactor;
        safetyFactor -= weights[cow];
        safetyFactor = min(safetyFactor, strengths[cow]);

        total_h += heights[cow];

        if( total_h >= H ) answer = max(answer, safetyFactor);

        dfs( i + 1 );

        safetyFactor = oldSafety;
        total_h -= heights[cow];

    }

    dfs(i + 1);   

}

bool cmp(long long a, long long b){
    return weights[a] + strengths[a] > weights[b] + strengths[b];
}

int main(){
	

    scanf("%d %lld", &N, &H);

	for(int i = 0; i < N; i++){
		scanf("%lld %lld %lld", &heights[i], &weights[i], &strengths[i]);
        indicies[i] = i;
    }

    sort(indicies, indicies + N, cmp);
    

    dfs(0);

   if(answer == -1){
      printf("Mark is too tall\n");
      return 0;
   }

   printf("%lld\n", answer);

	return 0;
}