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

using Tuple = tuple<deque<size_t>, deque<size_t>, bool>;
using Pair = pair<deque<size_t>, deque<size_t>>;


vector<size_t> get_vect(deque<size_t> p1, deque<size_t> p2) {
	vector<size_t> result;

	for (size_t i : p1) result.push_back(i);
	result.push_back(0);
	for (size_t i : p2) result.push_back(i);

	return result;
}


Tuple play_game(deque<size_t> p1, deque<size_t> p2, bool recurse) {
	set<vector<size_t>> rounds;
	unordered_set<string> previous_rounds;

	while (!(p1.size() == 0 || p2.size() == 0)) {

		const vector<size_t> v = get_vect(p1, p2);

		if (rounds.find(v) != rounds.end()) {
			return { p1, p2, true };
		}

		rounds.insert(v);

		size_t p1_card = p1[0];
		size_t p2_card = p2[0];

		p1.pop_front();
		p2.pop_front();

		bool winner;
		if (recurse && p1_card <= p1.size() && p2_card <= p2.size()) {
			deque<size_t> p1_c = p1;
			deque<size_t> p2_c = p2;

			p1_c.resize(p1_card);
			p2_c.resize(p2_card);

			winner = get<2>(play_game(p1_c, p2_c, true));
		}
		else {
			winner = p1_card > p2_card;
		}

		if (winner) {
			p1.push_back(p1_card);
			p1.push_back(p2_card);
		}
		else {
			p2.push_back(p2_card);
			p2.push_back(p1_card);
		}
	}
	return { p1, p2, p1.size() > p2.size() };
}

int main() {
	ifstream input("C:\\Users\\Martijn\\Desktop\\Advent Of Code\\AoC2020\\AoC2020\\input\\2020_22.txt");

	string x;
	bool p2 = true;

	deque<size_t> player1;
	deque<size_t> player2;

	while (getline(input, x)) {
		if (x[0] == 'P') { 
			p2 = p2 ? false : true;
			continue; 
		}
		if (x.compare("") == 0) continue;
		
		if(!p2) player1.push_back(stoi(x));
		else player2.push_back(stoi(x));
	}

	Tuple result = play_game(player1, player2, true);


	deque<size_t> winner = get<2>(result) ? get<0>(result) : get<1>(result);

	int answer = 0;
	for (size_t i = 0; i < winner.size(); i++) {
		answer += winner[i] * (winner.size() - i);
	}
	cout << answer << endl;

}