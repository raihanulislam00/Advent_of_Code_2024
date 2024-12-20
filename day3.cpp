#include <iostream>
#include <fstream>
#include <cassert>
#include <cctype>
#include <string>
using namespace std;

enum MulState {
    START = 0,   // No active parse
    M,           // "m"
    MU,          // "mu"
    MUL,         // "mul"
    MULO,        // "mul("
    MULOX, MULOXX, MULOXXX, // "mul(###"
    MULOXC,      // "mul(###,"
    MULOXCY, MULOXCYY, MULOXCYYY, // "mul(###,###"
    MULOXCYE,    // "mul(###,###)"
    DO,          // "do"
    DOO,         // "do("
    DOOE,        // "do()"
    DON,         // "don"
    DONA,        // "don't"
    DONATO,      // "don't("
    DONATOE      // "don't()"
};

struct MulStateData {
    MulState state;
    int first;
    int second;

    void reset() {
        state = START;
        first = 0;
        second = 0;
    }

    void update(char ch) {
        if (ch == 'm') {
            reset();
            state = M;
        } else if (ch == 'd') {
            reset();
            state = DO;
        } else if (state == M && ch == 'u') {
            state = MU;
        } else if (state == MU && ch == 'l') {
            state = MUL;
        } else if (state == MUL && ch == '(') {
            state = MULO;
        } else if (state == MULO && isdigit(ch)) {
            state = MULOX;
            first = ch - '0';
        } else if (state == MULOX && isdigit(ch)) {
            state = MULOXX;
            first = first * 10 + (ch - '0');
        } else if (state == MULOXX && isdigit(ch)) {
            state = MULOXXX;
            first = first * 10 + (ch - '0');
        } else if ((state == MULOX || state == MULOXX || state == MULOXXX) && ch == ',') {
            state = MULOXC;
        } else if (state == MULOXC && isdigit(ch)) {
            state = MULOXCY;
            second = ch - '0';
        } else if (state == MULOXCY && isdigit(ch)) {
            state = MULOXCYY;
            second = second * 10 + (ch - '0');
        } else if (state == MULOXCYY && isdigit(ch)) {
            state = MULOXCYYY;
            second = second * 10 + (ch - '0');
        } else if ((state == MULOXCY || state == MULOXCYY || state == MULOXCYYY) && ch == ')') {
            state = MULOXCYE;
        } else if (state == DO && ch == 'o') {
            state = DOO;
        } else if (state == DOO && ch == '(') {
            state = DOOE;
        } else if (state == DO && ch == 'n') {
            state = DON;
        } else if (state == DON && ch == '\'') {
            state = DONA;
        } else if (state == DONA && ch == 't') {
            state = DONATO;
        } else if (state == DONATO && ch == '(') {
            state = DONATOE;
        } else {
            reset();
        }
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input1.text", "r", stdin);
    freopen("output1.text", "w", stdout);
#endif

    ifstream inputFile("input1.text");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    MulStateData data;
    data.reset();
    int part1 = 0;
    int part2 = 0;
    bool isEnabled = true;
    char ch;

    while (inputFile.get(ch)) {
        assert(ch >= 0 && ch <= 127);
        data.update(ch);

        if (data.state == MULOXCYE) {
            int value = data.first * data.second;
            part1 += value;
            if (isEnabled) {
                part2 += value;
            }
        } else if (data.state == DOOE) {
            isEnabled = true;
        } else if (data.state == DONATOE) {
            isEnabled = false;
        }
    }

    inputFile.close();

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;

    return 0;
}
