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
#include <array>

using namespace std;


const int width = 10;
const int height = 10;


struct Tile {
	int id;

	array<string, height - 2> data;

	//north, south, west, east
	vector<int> sides;
	vector<int> r_sides;

	tuple<int, int, bool> side_ids[4];

	int filled_sides = 0;
};

using Pair = pair<const int, Tile>;

Tile fill_info(int id, vector<string> buffer) {
	Tile result;
	result.id = id;

	for(int i = 1; i < height - 1; i++){
		result.data[i-1] = buffer[i].substr(1, width-2);
	}

	string s = "";
	for (char c : buffer[0]) {
		if (c == '#') s += "1";
		else s += "0";
	}
	//cout << s << endl;
	result.sides.push_back(bitset<width>(s).to_ulong());
	reverse(s.begin(), s.end());
	result.r_sides.push_back(bitset<width>(s).to_ulong());

	s = "";
	for (char c : buffer[height-1]) {
		if (c == '#') s += "1";
		else s += "0";
	}
	//cout << s << endl;
	result.sides.push_back(bitset<width>(s).to_ulong());
	reverse(s.begin(), s.end());
	result.r_sides.push_back(bitset<width>(s).to_ulong());

	string w = "";
	string e = "";
	for (int i = 0; i < height; i++) {
		if (buffer[i][0] == '#') w += "1";
		else w += "0";

		if (buffer[i][width-1] == '#') e += "1";
		else e += "0";
	}
	//cout << w << endl;
	//cout << e << endl;
	result.sides.push_back(bitset<width>(w).to_ulong());
	reverse(w.begin(), w.end());
	result.r_sides.push_back(bitset<width>(w).to_ulong());

	result.sides.push_back(bitset<width>(e).to_ulong());
	reverse(e.begin(), e.end());
	result.r_sides.push_back(bitset<width>(e).to_ulong());

	return result;
}

array<string, height - 2> rotate(array<string, height - 2> buffer, int extra_rotations) {
	array<string, height - 2> result;

	for(int i = 0; i < width - 2; i++){
		string s = "";

		for (int j = 0; j < height - 2; j++) {
			s += buffer[height - j - 3][i];
		}
		//cout << s << endl;
		result[i] = s;
	}
	//cout << endl;
	if (extra_rotations > 0) {
		return(rotate(result, extra_rotations - 1));
	}
	else {
		return result;
	}
	
}

array<string, height - 2> mirror(array<string, height - 2> buffer) {
	array<string, height - 2> result;

	for (int i = 0; i < (height - 1)/2; i++) {
		result[i] = buffer[height - i - 3];
		result[height - 3 - i] = buffer[i];
	}
	//cout << endl;
	return result;
}


int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_20.txt");

	string x;
	unordered_map<int, Tile> tiles;
	vector<string> buffer;
	int id;

	while (getline(input, x)) {
		if (x.compare("") == 0) {

			tiles[id] = fill_info(id, buffer);

			buffer.clear();
		} else if (x[0] == 'T') {
			id = stoi(x.substr(5, 4));
		}
		else {
			buffer.push_back(x);
		}
	}

	unsigned long long answer = 1;
	Tile last_tile;
	for (Pair p : tiles) {
		Tile t_ = p.second;
		for (Pair o_p : tiles) {
			if (p.first == o_p.first) continue;

			for (int i = 0; i < 4; i++){
				int side = t_.sides[i];

				for (int side_id = 0; side_id < 4; side_id++) {
					int o_side = o_p.second.sides[side_id];
					if (side == o_side) {
						t_.filled_sides++;
						//cout << t.id << ": " << i << ": " << o_t.id << endl;
						t_.side_ids[i] = { o_p.first , side_id, false };

					}
					else {
						o_side = o_p.second.r_sides[side_id];
						if (side == o_side) {
							t_.filled_sides++;
							//cout << t.id << ": " << i << ": " << o_t.id << endl;
							t_.side_ids[i] = { o_p.first , side_id, true };

						}
					}
				}
			}
		}
		if (t_.filled_sides == 2) {
			answer *= p.first;
			last_tile = t_;
		}

		tiles[p.first] = t_;
	}
	cout << answer << endl;


	last_tile = tiles.find(1951)->second;

	array<string, 120> picture;


	Tile RowStart = last_tile;

	bool flipped = true;
	int ingoing_side = 3;
	int start_row = 0;

	

	array<string, height - 2> cur_data = last_tile.data;

	if(flipped) cur_data = mirror(cur_data);

	while(true){

		while(true){
			cout << last_tile.id << endl;
			for (int i = start_row; i < start_row + height - 2; i++) {
				picture[i] = picture[i] + cur_data[i % 8] + " ";
			}

			tuple<int, int, bool> next_id = last_tile.side_ids[ingoing_side];
			int nid = get<0>(next_id);
			if (get<0>(next_id) == 0) break;
			Tile next_tile = tiles.find(get<0>(next_id))->second;

			cur_data = next_tile.data;

			if (get<1>(next_id) == 0) {
				cur_data = rotate(cur_data, 2);
			}
			else if (get<1>(next_id) == 1) {
				cur_data = rotate(cur_data, 0);
			}
			else if (get<1>(next_id) == 3) {
				cur_data = rotate(cur_data, 1);
			}

			if (get<2>(next_id)) {
				flipped = flipped ? false : true;
			}

			if (flipped) {
				cur_data = mirror(cur_data);
			}

			int back_reference = get<1>(next_id);

			if (back_reference == 0) {
				ingoing_side = 1;
			}
			else if (back_reference == 1) {
				ingoing_side = 0;
			}
			else if (back_reference == 2) {
				ingoing_side = 3;
			}
			else {
				ingoing_side = 2;
			}

			last_tile = next_tile;
		}
		

		last_tile = RowStart;
		start_row += height - 2;



		tuple<int, int, bool> next_id = last_tile.side_ids[0];
		int nid = get<0>(next_id);
		if (get<0>(next_id) == 0) break;
		Tile next_tile = tiles.find(get<0>(next_id))->second;

		cur_data = next_tile.data;

		if (get<1>(next_id) == 1) {
			cur_data = rotate(cur_data, 1);
		}
		else if (get<1>(next_id) == 2) {
			cur_data = rotate(cur_data, 0);
		}
		else if (get<1>(next_id) == 3) {
			cur_data = rotate(cur_data, 2);
		}

		//flipped = false;
		if (get<2>(next_id)) {
			flipped == flipped ? false : true;
		}

		if (flipped) {
			cur_data = mirror(cur_data);
		}

		int back_reference = get<1>(next_id);

		if (back_reference == 0) {
			ingoing_side = get<2>(next_id) ? 3 : 2;
		}
		else if (back_reference == 1) {
			ingoing_side = get<2>(next_id) ? 2 : 3;
		}
		else if (back_reference == 2) {
			ingoing_side = get<2>(next_id) ? 1 : 0;
		}
		else {
			ingoing_side = get<2>(next_id) ? 0 : 1;
		}
		RowStart = next_tile;
		last_tile = next_tile;
		

	}



	for (int i = 0; i < 120; i++) {
		if (i % 8 == 0) cout << endl;
		cout << picture[i] << endl;
		
	}
	cout << answer << endl;
}
