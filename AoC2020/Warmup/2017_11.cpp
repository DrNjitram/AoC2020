#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>


using namespace std;

int main() {

	ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\Warmup\\input\\day11_2017.txt");
	stringstream buffer;
	buffer << input.rdbuf();
	istringstream is(buffer.str());


	int x = 0;
	int y = 0;
	int z = 0;
	int max = 0;

	string n;
	while (is >> n) {
		if (n == "se") {
			y--;
			x++;
		}
		else if (n == "s") {
			y--;
			z++;
		}
		else if (n == "sw") {
			x--;
			z++;
		}
		else if (n == "ne") {
			x++;
			z--;
		}
		else if (n == "n") {
			y++;
			z--;
		}
		else if (n == "nw") {
			y++;
			x--;
		}
		int dist = (abs(x) + abs(y) + abs(z)) / 2;
		if (dist > max) max = dist;
	}

	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	cout << max << endl;
	cout << (abs(x) + abs(y) + abs(z)) / 2 << endl;
}