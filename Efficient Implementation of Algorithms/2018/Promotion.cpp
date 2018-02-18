/*
The cows have once again tried to form a startup company, failing to remember from past experience that cows make terrible managers! 

The cows, conveniently numbered 1…N (1≤N≤100,000), organize the company as a tree, with cow 1 as the president (the root of the tree). Each cow except the president has a single manager (its "parent" in the tree). Each cow i has a distinct proficiency rating, p(i), which describes how good she is at her job. If cow i is an ancestor (e.g., a manager of a manager of a manager) of cow j, then we say j is a subordinate of i. 

Unfortunately, the cows find that it is often the case that a manager has less proficiency than several of her subordinates, in which case the manager should consider promoting some of her subordinates. Your task is to help the cows figure out when this is happening. For each cow i in the company, please count the number of subordinates j where p(j)>p(i).

Input
The first line of input contains N. 

The next N lines of input contain the proficiency ratings p(1)…p(N) for the cows. Each is a distinct integer in the range 1…1,000,000,000. 

The next N−1 lines describe the manager (parent) for cows 2…N. Recall that cow 1 has no manager, being the president.

Output
Please print N lines of output. The ith line of output should tell the number of subordinates of cow i with higher proficiency than cow i.

Example
Input
5
804289384
846930887
681692778
714636916
957747794
1
1
2
3
Output
2
0
1
0
0

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;



const int N = 1048576;
int tree_size = 1;

int interval_tree[2*N + 7];

pair<int, int> p[N];
vector<int> tree[N];

pair<int, int> pre_order[N];

int result[N];

void clear_tree(int k){
	tree_size = 1;
	while(tree_size < k) tree_size *= 2;

	for(int i = 0; i < 2*tree_size + 7; i++){
		interval_tree[i] = 0;
	}
}

void add(int i){
	int v = tree_size + i;

	interval_tree[ v ]++;

	while( v / 2 > 0){
		interval_tree[v / 2]++;
		v /= 2;
	}
}

void remove(int i){
	int v = tree_size + i;

	interval_tree[ v ]--;

	while( v / 2 > 0){
		interval_tree[v / 2]--;
		v /= 2;
	}
}


int query(int a, int b){
	int va = tree_size + a, vb = tree_size + b;
	if(va == vb){
		return interval_tree [ va ];
	}

	int sum = interval_tree[ va ] + interval_tree [ vb ];

	while( va / 2 != vb / 2){
		if(va % 2 == 0) sum += interval_tree[ va + 1 ];
		if(vb % 2 == 1) sum += interval_tree[ vb - 1 ];
		va /= 2;
		vb /= 2;
	}

	return sum;
}


int I = 1;

void do_pre_order(int v){
	pre_order [ v ].first = I++;

	for(int i = 0; i < tree[v].size(); i++)
		do_pre_order( tree[v][i] );

	pre_order[ v ].second = I - 1;

}



bool cmp(pair<int, int> a, pair<int, int> b){
	return a.first > b.first;
}


int main(){

	int n, a;

	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a);
		p[i] = make_pair(a, i);
	}

	for(int i = 2; i <= n; i++){
		scanf("%d", &a);
		tree[a].push_back(i);
	}


	do_pre_order(1);

	sort(p + 1, p + n + 1, cmp);

	clear_tree( n );

	for(int i = 1; i <= n; i++){
		result[ p[i].second ] = query( pre_order[ p[i].second ].first, pre_order[ p[i].second ].second );

		add( pre_order[ p[i].second ].first );
	}

	for(int i = 1; i <= n; i++){
		printf("%d\n", result[i]);
	}

	return 0;
}