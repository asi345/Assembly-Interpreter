//
//  variables.cpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include <iostream>

#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

ifstream input;

unordered_set<string> reg16;
unsigned short ax = 0;
unsigned short bx = 0;
unsigned short cx = 0;
unsigned short dx = 0;
unsigned short di = 0;
unsigned short sp = (1 << 16) - 2;
unsigned short si = 0;
unsigned short bp = 0;

unordered_map<string, unsigned short *> reg16Values;

unordered_set<string> reg8;
unsigned char ah = 0;
unsigned char al = 0;
unsigned char bh = 0;
unsigned char bl = 0;
unsigned char ch = 0;
unsigned char cl = 0;
unsigned char dh = 0;
unsigned char dl = 0;

unordered_map<string, unsigned char *> reg8Values;

bool zf = false;
bool cf = false;
bool sf = false;
bool of = false;
bool af = false;

string nextLabel;

unordered_map<string, int> labelLines;

unordered_map<string, vector<vector<string> > > blocks;

vector<string> labels;

unordered_map<string, int> addresses;

unordered_map<string, char> types;

vector<unsigned char> memory((1 << 16), 0);