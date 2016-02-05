// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

#define CACHE

static int cache[1000];

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i >= 1 && i <= 1000000);
    assert(j >= 1 && j <= 1000000);
    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }
    assert(i <= j);
    int max = -1;
    do {
        int steps = 1;
        int n = i;
        while (n > 1) {
            #ifdef CACHE
                if (n < 1000 && cache[n] != 0) {
                    steps += cache[n] - 1;
                    break;
                }
            #endif
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
            steps++;
        }
        if (steps > max) {
            max = steps;
        }
        #ifdef CACHE
            if (i < 1000 && cache[i] == 0) {
                cache[i] = steps;
            }
        #endif
    } while (++i <= j);
    assert(max >= 1);
    return max;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
