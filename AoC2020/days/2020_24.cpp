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

struct key_hash {
	size_t operator()(const pair<int, int>& k) const {
		size_t h = 0;

		h ^= hash<int>{}(k.first) + 0x9e3779b9 + (h << 6) + (h >> 2);
		h ^= hash<int>{}(k.second) + 0x9e3779b9 + (h << 6) + (h >> 2);

		return h;
	}
};

using Pair = pair<pair<int, int>, bool>;
using Map = unordered_map<pair<int, int>, bool, key_hash>;


Map do_day(Map tiles) {
	int neigh_x[] = {-1, 0, 1, 1, 0, -1};
	int neigh_y[] = {1, 1, 0, -1, -1, 0};

	unordered_map<pair<int, int>, int, key_hash> neigh_fill;
	Map new_dim;

	for (Pair tile : tiles) {
		if (!tile.second) continue;
		for (int i = 0; i < 6; i++) {
			neigh_fill[{tile.first.first + neigh_x[i], tile.first.second + neigh_y[i]}]++;
		}
	}

	for (const Pair& tile : tiles) {
		if (!tile.second) continue;

		if (neigh_fill[tile.first] == 1 || neigh_fill[tile.first] == 2) new_dim[tile.first] = true;
	}

	for (const pair<pair<int, int>, int>& tile : neigh_fill) {
		if (tile.second != 2) continue;

		new_dim[tile.first] = true;
	}

	return new_dim;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_24.txt");

	Map tiles;
	int max = 0;
	string n;

	auto start = chrono::high_resolution_clock::now();
	while (getline(input, n)) {

		int x = 0;
		int y = 0;


		for (int i = 0; i < n.length(); i++) {
	
			if (n[i] == 's' && n[i + 1] == 'e') {//se
				i++;
				y--;
			}
			else if (n[i] == 'e') { //e
				y--;
				x++;
			}
			else if (n[i] == 's' && n[i + 1] == 'w') {//sw
				i++;
				x--;

			}
			else if (n[i] == 'n' && n[i + 1] == 'e') {//ne
				i++;
				x++;
			}
			else if (n[i] == 'w') {//w
				y++;
				x--;
			}
			else if (n[i] == 'n' && n[i + 1] == 'w') {//nw
				i++;
				y++;
			}
		}
		pair<int, int> pos = { x , y };

		if (tiles.find(pos) == tiles.end()) {
			tiles[pos] = true;
		}
		else {
			tiles[pos] = tiles[pos] ? false : true;
		}

	}

	int answer1 = 0;

	for (Pair p : tiles) {
		if (p.second) answer1++;
	}

	for (int i = 0; i < 100; i++) {
		Map result = do_day(tiles);
		tiles = result;
	}

	int answer2 = 0;

	for (Pair p : tiles) {
		if (p.second) answer2++;
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

	cout << "Day 0: " << answer1 << endl;
	cout << "Day 100: " << answer2 << endl;

	cout << "Time(ms): " << duration.count() << endl;
}