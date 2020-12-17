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

using namespace std;

using Tuple = tuple<int, int, int, int>;
using Pair = pair<Tuple, bool>;

struct key_hash
{
	std::size_t operator()(const Tuple& k) const
	{
		return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k) ^ std::get<3>(k);
	}
};

unordered_map<Tuple, bool, key_hash> pocket_dimension;


void do_cycle() {
	unordered_map<Tuple, int, key_hash> neigh_fill;
	unordered_map<Tuple, bool, key_hash> new_dim;

	for (Pair p : pocket_dimension) {
		if (!p.second) continue;
		for (int z = -1; z <= 1; z++) {
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					for (int w = -1; w <= 1; w++) {
						if (x == 0 && y == 0 && z == 0 && w == 0) continue;
						neigh_fill[{x + get<0>(p.first), y + get<1>(p.first), z + get<2>(p.first), w + get<3>(p.first)}]++;
					}
				}
			}
		}
	}

	for (Pair p : pocket_dimension) {
		if (!p.second) continue;
		if (neigh_fill[p.first] == 2 || neigh_fill[p.first] == 3) new_dim[p.first] = true;
	}

	for (pair<Tuple, int> p : neigh_fill) {
		if (p.second != 3) continue;

		unordered_map<Tuple, bool, key_hash>::iterator it = pocket_dimension.find(p.first);
		if (it != pocket_dimension.end()) {
			if (it->second == false) new_dim[p.first] = true;
		}
		else new_dim[p.first] = true;
	}

	pocket_dimension = new_dim;
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_17.txt");

	string x;
	int r = 0;

	while (getline(input, x)) {
		for (int i = 0; i < x.length(); i++) {
			if (x[i] == '#') pocket_dimension[{i, r, 0, 0}] = true;
		}
		r++;
	}
	
	auto start = chrono::high_resolution_clock::now();

	for(int i = 0; i < 6; i++)
		do_cycle();

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

	cout << pocket_dimension.size() << endl;

	cout << "Time(ms): " << duration.count() << endl;
}