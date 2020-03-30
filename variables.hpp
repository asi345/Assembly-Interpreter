//
//  variables.hpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#ifndef variables_hpp
#define variables_hpp

#include <iostream>

#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Reads lines from the file.
extern ifstream input;

// 16 bit registers
extern unordered_set<string> reg16;
extern unsigned short ax;
extern unsigned short bx;
extern unsigned short cx;
extern unsigned short dx;
extern unsigned short di;
extern unsigned short sp;
extern unsigned short si;
extern unsigned short bp;

// Allows reaching 16 bit registers using their name in string.
extern unordered_map<string, unsigned short *> reg16Values;

// 8 bit registers
extern unordered_set<string> reg8;
extern unsigned char ah;
extern unsigned char al;
extern unsigned char bh;
extern unsigned char bl;
extern unsigned char ch;
extern unsigned char cl;
extern unsigned char dh;
extern unsigned char dl;

// Allows reaching 8 bit registers using their names in string.
extern unordered_map<string, unsigned char *> reg8Values;

// Flags
extern bool zf;
extern bool cf;
extern bool sf;
extern bool of;
extern bool af;

// Keeps the label to be jumped when jump instruction is performed
extern string nextLabel;

// Connects labels with their line numbers.
extern unordered_map<string, int> labelLines;

// Connects labels with their block. A block is kept in an array.
extern unordered_map<string, vector<vector<string> > > blocks;

/* Keeps labels in the order in which the one read from the file first appears first in the vector.
 Allows iterating through the *blocks* map in the correct order.
*/
extern vector<string> labels;

// Connects variable names with their memory addresses.
extern unordered_map<string, int> addresses;

// Connects varibale names with their storage in the memory (byte, word)
extern unordered_map<string, char> types;

// Connects memory addresses with their contents (a cell holds 1 byte).
extern vector<unsigned char> memory;

#endif /* variables_hpp */