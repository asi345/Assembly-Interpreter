//
// Created by MONSTER on 22.3.2020.
//

#include <stdio.h>

#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Reads lines from the file.
ifstream input;

// 16 bit registers
unordered_set<string> reg16;
unsigned short ax = 0;
unsigned short bx = 0;
unsigned short cx = 0;
unsigned short dx = 0;
unsigned short di = 0;
unsigned short sp = (1 << 16) - 2;
unsigned short si = 0;
unsigned short bp = 0;

// Allows reaching 16 bit registers using their name in string.
unordered_map<string, unsigned short *> reg16Values;

// 8 bit registers
unordered_set<string> reg8;
unsigned char ah = 0;
unsigned char al = 0;
unsigned char bh = 0;
unsigned char bl = 0;
unsigned char ch = 0;
unsigned char cl = 0;
unsigned char dh = 0;
unsigned char dl = 0;

// Allows reaching 8 bit registers using their names in string.
unordered_map<string, unsigned char *> reg8Values;

// Flags
bool zf = false;
bool cf = false;
bool sf = false;
bool of = false;
bool af = false;

string nextLabel;

// Connects labels with their line numbers.
unordered_map<string, int> labelLines;

// Connects labels with their block. A block is kept in an array.
unordered_map<string, vector<vector<string> > > blocks;

/* Keeps labels in the order in which the one read from the file first appears first in the vector.
 Allows iterating through the *blocks* map in the correct order.
*/
vector<string> labels;

// Connects variable names with their memory addresses.
unordered_map<string, int> addresses;

// Silinebilir, offset kendisi size ayarlıyor
// Connects varibale names with their storage in the memory (byte, word, doubleword)
unordered_map<string, char> types;

// Connects memory addresses with their contents (a cell holds 1 byte).
vector<unsigned char> memory((1 << 16), 0);