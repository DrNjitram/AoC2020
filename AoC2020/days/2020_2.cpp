#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>


using namespace std;


int part1(smatch sm) {
    int lower = stoi(sm[1]);
    int upper = stoi(sm[2]);

    string character = sm[3];

    string password = sm[4];

    int count = 0;
    for (const char& c : password) {
        string s(1, c);
        if (character.compare(s) == 0) count++;
    }

    if (count <= upper && count >= lower) {
        return 1;
    }
    return 0;
}


int part2(smatch sm) {
    int pos1 = stoi(sm[1]);
    int pos2 = stoi(sm[2]);

    string character = sm[3];
    string password = sm[4];

    return (password[pos1 - 1] == character[0]) ^ (password[pos2 - 1] == character[0]);
}

int main() {
    ifstream input("C:\\Users\\Martijn\\Desktop\\AoC2020\\AoC2020\\input\\2020_2.txt");

    string x;

    //1: register, 2: dec/inc, 3: val, 4: cond_reg, 5: cond_cond, 6: cond_val 
    regex rule("(\\d+)-(\\d+) ([a-z]): (\\w+)");    

    int valid1 = 0;
    int valid2 = 0;

    if (input.is_open()) {
        while (getline(input, x)) {

            smatch sm;
            regex_match(x, sm, rule);

            valid1 += part1(sm);
            valid2 += part2(sm);
        }
    }

    cout << valid1 << endl;
    cout << valid2 << endl;
}