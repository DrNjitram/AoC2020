#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <deque>

using namespace std;

int main() {
	const string input = "326519478";

	const int total_cups = 1'000'000;//1000000;
	//total_cups = 9;

	const int turns = 10'000'000;//10'000'000

	vector<int> cups;

	const int current_cup = 1;

	for (const char& c : input)
		cups.push_back(c - (int)'0');

	cups.resize(total_cups);

	for (int i = input.length(); i < total_cups; i++) {
		cups[i] = i + 1;
	}

	rotate(cups.begin(), cups.end() - 1, cups.end());

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < turns; i++) {
		if (i % 100'000 == 0) cout << i << endl;
		int destination_cup_value = (cups[current_cup] - 1);
		if (destination_cup_value == 0) destination_cup_value = total_cups;
		int destination_cup = 0;

		rotate(cups.begin(), cups.begin() + current_cup, cups.end());

		array<int, 3> pickup;

		copy(cups.begin() + 1, cups.begin() + 4, pickup.begin());

		cups.erase(cups.begin() + 1, cups.begin() + 4);

		for (int _ = 0; _ < 3; _++) {
			if (destination_cup_value == pickup[0] ||
				destination_cup_value == pickup[1] ||
				destination_cup_value == pickup[2]
				)destination_cup_value--;
			if (destination_cup_value == 0) destination_cup_value = total_cups;
		}

		vector<int>::iterator it = find(cups.begin(), cups.end(), destination_cup_value);
		int index = distance(cups.begin(), it);

		cups.insert(cups.begin() + index + 1, pickup.begin(), pickup.end());
	}

	vector<int>::iterator it = find(cups.begin(), cups.end(), 1);
	int index = distance(cups.begin(), it);

	long long answer = 1;
	answer *= cups[(index + 1) % total_cups];
	answer *= cups[(index + 2) % total_cups];

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

	cout << cups[(index + 1) % total_cups];
	cout << cups[(index + 2) % total_cups];

	if (total_cups == 9) {
		for (int ull : cups)
			cout << ull;
		cout << endl;
	}

	cout << answer << endl;
	cout << "Time(ms): " << duration.count() << endl;

	// debug ans 158802

	//44541319250 finally
}

/*
 *
 * Dont raise your voice, improve your argument.
 * --Desmond Tutu
 

#include <bits/stdc++.h>
using namespace std;

const bool ready = []() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout << fixed << setprecision(12);
	return true;
}();

using ld = long double;
const ld PI = acos(-1);
using ll = long long;
#define int ll
#define all(v) (v).begin(), (v).end()
#define fori(n) for(int i=0; i<int(n); i++)

#define cini(i) int i; cin>>i;
#define cins(s) string s; cin>>s;
#define cind(d) ld d; cin>>d;
#define cinai(a,n) vi a(n); fori(n) { cin>>a[i]; }
#define cinas(s,n) vs s(n); fori(n) { cin>>s[i]; }
#define cinad(a,n) vd a(n); fori(n) { cin>>a[i]; }

using pii = pair<int, int>;
using pdd = pair<ld, ld>;
using vd = vector<ld>;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using vs = vector<string>;

#define endl "\n"

*
 * star2:
 * Simple simulation seems to lame.
 *
 * We got 3 operations on the ring:
 * pos: find position of an element ( to find dest in each step )
 * rem: remove 3 elements from consecutive positions
 * ins: insert 3 elements at consecutive positions
 * ***
 * maintain a map<val,next> to do the operations in O(logn)
 *

const int M = 1e7;
const int N = 1e6;
void solve() {
	const vi a = { 3,2,6,5,1,9,4,7,8 }; // original input

	unordered_map<int, int> next;

	for (size_t i = 0; i + 1 < a.size(); i++)
		next[a[i]] = a[i + 1];

	next[8] = 10;
	for (int i = 10; i < N; i++)
		next[i] = i + 1;
	next[N] = 3;      // link back to first 

	int cur = a[0];   // first element of input 

	for (int i = 0; i < M; i++) {
		vi rmvals(3);
		for (int j = 0; j < 3; j++) {
			rmvals[j] = next[cur];
			next[cur] = next[rmvals[j]];
		}

		int dest = cur - 1;
		if (dest == 0)
			dest += N;

		while (dest == rmvals[0] || dest == rmvals[1] || dest == rmvals[2]) {
			dest = dest - 1;
			if (dest == 0)
				dest += N;
		}

		// insert the three elements 
		next[rmvals[2]] = next[dest];
		next[rmvals[1]] = rmvals[2];
		next[rmvals[0]] = rmvals[1];
		next[dest] = rmvals[0];

		// advance one position 
		cur = next[cur];
	}

	long long a1 = next[1];
	long long a2 = next[a1];

	long long ans = a1 * a2;
	cout << ans << endl;
}

signed main() {
	solve();
}
*/