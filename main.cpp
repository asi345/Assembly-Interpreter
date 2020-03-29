//
//  main.cpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include <iostream>
#include <algorithm>

#include "operation.hpp"
#include "variables.hpp"

using namespace std;

bool initialize();
bool readLines();
bool run();
void printFinalState();

int main(int argc, const char * argv[]) {
    // : içeren var def yok
    // ilk substr den sonra popbackten önce isEmpty
    // w var1 WTFF
    // negative number
    input.open(argv[1]);
    bool isTrue = initialize();
    if (!isTrue)
        return 0;
    isTrue = readLines();
    if (!isTrue)
        return 0;
    isTrue = run();
    if (!isTrue)
        return 0;
    printFinalState();
    input.close();
    return 0;
}

bool initialize() {

    // Controls if the ifstream is working properly.
    if (!input.is_open()) {
        cout << "File can not be found." << endl;
        return false;
    }

    reg16.insert("ax");
    reg16.insert("bx");
    reg16.insert("cx");
    reg16.insert("dx");
    reg16.insert("di");
    reg16.insert("sp");
    reg16.insert("si");
    reg16.insert("bp");
    reg8.insert("ah");
    reg8.insert("al");
    reg8.insert("bh");
    reg8.insert("bl");
    reg8.insert("ch");
    reg8.insert("cl");
    reg8.insert("dh");
    reg8.insert("dl");

    // Initializes maps that holds register value pointers.
    reg16Values["ax"] = &ax;
    reg16Values["bx"] = &bx;
    reg16Values["cx"] = &cx;
    reg16Values["dx"] = &dx;
    reg16Values["di"] = &di;
    reg16Values["sp"] = &sp;
    reg16Values["si"] = &si;
    reg16Values["bp"] = &bp;
    reg8Values["ah"] = &ah;
    reg8Values["al"] = &al;
    reg8Values["bh"] = &bh;
    reg8Values["bl"] = &bl;
    reg8Values["ch"] = &ch;
    reg8Values["cl"] = &cl;
    reg8Values["dh"] = &dh;
    reg8Values["dl"] = &dl;

    /* If the given Assembly code does not start with a label, puts the code block
     without a label in the beginning in a label called *untitled*.
    */
    labels.push_back("untitled");

    /* Declares that the *untitled* label starts at line *0* so that it does not affect
     the line numbers of other lines.
    */
    labelLines["untitled"] = 0;

    return true;
}

bool readLines() {
    string line, curLabel = "untitled";
    int lineNum = 0, address = 0;
    bool isSegment = true;
    vector<string> tokens;
    vector<vector<string> > block;
    string::iterator it;
    while (getline(input, line)) {
        lineNum++;
        if (line.back() == '\r')
            line.pop_back();
        int space = 0;
        while (space != line.size() && line.at(space) == ' ')
            space++;
        line = line.substr(space);
        while (!line.empty() && line.back() == ' ')
            line.pop_back();
        if (line.empty()) {
            block.push_back(vector<string> (3, ""));
            continue;
        }
        for (it = line.begin(); it != line.end(); it++)
            *it = tolower(*it);
        if (!line.compare("nop")) {
            block.push_back(vector<string> (3, ""));
            address += 6;
            continue;
        }
        if (line.back() == ':') {
            line.pop_back();
            labels.push_back(line);
            labelLines[line] = lineNum;
            blocks[curLabel] = block;
            block.clear();
            curLabel = line;
        } else {
            space = line.find(' ');
            if (space == line.npos) {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
            string ins = line.substr(0, space);
            int redSpace = space + 1;
            while (line.size() != redSpace && line.at(redSpace) == ' ')
                redSpace++;
            line.erase(space + 1, redSpace - space - 1);
            if (space + 1 == line.size()) {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
            string operands = line.substr(space + 1);
            if (isSegment) {
                if (ins.compare("code") || operands.compare("segment")) {
                    cout << "\"code segment\" line can not be found.";
                    return false;
                } else {
                    block.push_back(vector<string> (3, ""));
                    isSegment = false;
                    continue;
                }
            }
            string operand1, operand2;
            int comma = operands.find(',');
            if (operands.back() == ',') {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            } else if (comma == operands.npos) {
                operand1 = operands;
                operand2 = "";
            } else {
                operand1 = operands.substr(0, comma);
                while (!operand1.empty() && operand1.back() == ' ')
                    operand1.pop_back();
                if (operand1.empty()) {
                    cout << "Syntax error at line " << lineNum << endl;
                    return false;
                }
                operand2 = operands.substr(comma + 1);
                redSpace = 0;
                while (redSpace != operand2.size() && operand2.at(redSpace) == ' ')
                    redSpace++;
                operand2 = operand2.substr(redSpace);
            }
            tokens.push_back(ins);
            tokens.push_back(operand1);
            tokens.push_back(operand2);
            block.push_back(tokens);
            tokens.clear();
            address += 6;
            if (!ins.compare("int") && !operand1.compare("20h") && !operand2.compare("")) {
                break;
            }
        }
    }
    blocks[curLabel] = block;
    while (getline(input, line)) {
        lineNum++;
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;
        if (!operation::defineVar(line, lineNum, address, isSegment))
            return false;
    }
    if (!isSegment)
        cout << "\"code ends\" line can not be found.";
    return isSegment;
}

bool run() {
    vector<string>::iterator it;
    for (it = labels.begin(); it != labels.end(); it++) {
        bool isRun = operation::process(blocks.at(*it), labelLines.at(*it));
        if (!isRun) {
            if (nextLabel.empty())
                return false;
            else if (!nextLabel.compare("int20h"))
                return true;
            else
                it = find(labels.begin(), labels.end(), nextLabel) - 1;
        }
    }
    return true;
}

void printFinalState() {
    cout << "ax :   " << ax << endl;
    cout << "bx :   " << bx << endl;
    cout << "cx :   " << cx << endl;
    cout << "dx :   " << dx << endl;
    cout << "di :   " << di << endl;
    cout << "sp :   " << sp << endl;
    cout << "si :   " << si << endl;
    cout << "bp :   " << bp << endl;
    cout << endl;
    cout << "zf :   " << zf << endl;
    cout << "cf :   " << cf << endl;
    cout << "sf :   " << sf << endl;
    cout << "of :   " << of << endl;
    cout << "af :   " << af << endl;
}