/* There are N cities in one country that are connected with two-way air links. One crazy airline president, Ronald Krump, often changes the flight schedule. More precisely, every day he does the following:

chooses one of the cities,
introduces flights from that city towards all other cities where these flights do not currently exist, and at the same time cancels all existing flights from that city
For instance, if from city 5 flights exist towards cities 1 and 2, but not towards cities 3 and 4, after Krump’s change, there will exist flights from city 5 towards cities 3 and 4, but not towards cities 1 and 2.
The citizens of this country are wondering if a day could come when the flight schedule will be complete. In other words, when between each two different cities a (direct) flight will exist. Write a programme that will, based on the current flight schedule, determine whether it is possible to have a Complete Day, or whether this will never happen, no matter what moves Krump makes.

Input
The first line of input contains the integer N (2 <= N <= 1000), the number of cities. The cities are labeled with numbers from 1 to N. The second line contains the integer M (0 <= M < N * (N - 1) / 2), the number of current flights. Each of the following M lines contains two different numbers, the labels of the cities that are currently connected.

Output
The first and only line of output must contain DA (Croatian for “yes”) or NE (Croatian for “no”).

Example 1
input

3 
2 
1 2 
2 3 
output
NE
Example 2
input

4 
2 
1 3 
2 4 
output
DA

Solution O(N + M), observation: if exactly two vertices from any 
three are connected the answer is always "NO". This pushes to the 
conclusion that given input must consist from two complete graphs 
in order to return "YES" (one graph can be empty). If given more 
than two, the situation from observation will appear after the 
first move.
*/
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

const int N = 1007;

vector<int> cities[N];
bool visited[N];

bool dfs_result = true;

void DFS(int v, int k){
	visited[ v ] = true;
	if( cities[v].size() != k ){
		dfs_result = false;
		return;
	}

	for(int i = 0; i < cities[v].size(); i++)
		if( !visited[cities[v][i]] ) DFS( cities[v][i], k );
}


int main(){
	
	int n, m, a, b;
	scanf("%d\n%d", &n, &m);

	while( m-- ){
		scanf("%d %d", &a, &b);
		cities[ a ].push_back(b);
		cities[ b ].push_back(a);
	}

	dfs_result = true;
	DFS(1, cities[1].size());
	if( !dfs_result ) {
		printf("NE\n");
		return 0;
	}
	int i = 2;
	while( i<=n && visited[ i ] ) i++;

	if( i <= n ) DFS(i, cities[i].size());
	if(!dfs_result){
		printf("NE\n");
		return 0;
	}

	while( i <= n ) {
		if( !visited[i] ){
			printf("NE\n");
			return 0;
		}
		i++;
	}


	printf("DA\n");


	return 0;
}