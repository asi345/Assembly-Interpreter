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

// Initializes the global variables and gets the system ready to parse.
bool initialize();

/* Reads all the lines in the code. The lines before "int 20h" is separated into tokens, leaving
 out whitespaces. Lines after "int 20h" are considered as variable definitions so *defineVar*
 function from *operation* namespace is called there.
 */
bool readLines();

/* Runs the code according to the order of the labels after all the lines are read and variables
 are defined. If a false is returned from any line, the function stops if the false is not
 because of a jump or int 20h.
*/
bool run();

/* If one wants to see the last state of all the registers and flags, this function can be called.
*/
void printFinalState();

int main(int argc, const char * argv[]) {
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
    // printFinalState();
    input.close();
    return 0;
}

bool initialize() {

    // Controls if the ifstream is working properly.
    if (!input.is_open()) {
        cout << "File can not be found." << endl;
        return false;
    }

    // Initializes the *reg16* and *reg8* sets
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
    // Labels are considered to be started from *untitled* because all lines should be in a label
    string line, curLabel = "untitled";
    int lineNum = 0, address = 0;
    // "Code segment" line is not encountered yet
    bool isSegment = true;
    // Instruction, operand1 and operand2 tokens
    vector<string> tokens;
    // Current block of code under current label
    vector<vector<string> > block;
    string::iterator it;
    while (getline(input, line)) {
        lineNum++;
        // Leave out the enter character
        if (line.back() == '\r')
            line.pop_back();
        // Clear the whitespaces
        int space = 0;
        while (space != line.size() && line.at(space) == ' ')
            space++;
        line = line.substr(space);
        while (!line.empty() && line.back() == ' ')
            line.pop_back();
        // Record the empty line because it affects the line numbers
        if (line.empty()) {
            block.push_back(vector<string> (3, ""));
            continue;
        }
        // Lowercase the line to understand it easily except if there is a char operand like 'A'
        for (it = line.begin(); it != line.end(); it++) {
            *it = tolower(*it);
            if (*it == '\'')
                it = line.begin() + line.find_last_of('\'');
        }
        // "Nop" instruction takes space in memory but counted as empty line
        if (!line.compare("nop")) {
            block.push_back(vector<string> (3, ""));
            address += 6;
            continue;
        }
        // If a label is encountered, record the current label and quit
        if (line.back() == ':') {
            line.pop_back();
            while (!line.empty() && line.back() == ' ')
                line.pop_back();
            if (line.empty() || line.find(' ') != line.npos || !isalpha(line.front())) {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
            labels.push_back(line);
            labelLines[line] = lineNum;
            blocks[curLabel] = block;
            block.clear();
            curLabel = line;
        } else {
            // If it is an instruction line
            space = line.find(' ');
            // There must be a space in the line between instruction and operand1
            if (space == line.npos) {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
            // Record the instruction
            string ins = line.substr(0, space);
            // Leave out the spaces after the instruction
            int redSpace = space + 1;
            while (line.size() != redSpace && line.at(redSpace) == ' ')
                redSpace++;
            line.erase(space + 1, redSpace - space - 1);
            // There must an operand1, because "nop" instruction is already handled
            if (space + 1 == line.size()) {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
            // Record the rest of the line containing operands
            string operands = line.substr(space + 1);
            // If the "code segment" line is encountered
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
            // There must be a comma between 2 operands
            int comma = operands.find(',');
            if (operands.back() == ',') {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
                // If there is 1 operand, then there should be no comma
            } else if (comma == operands.npos) {
                operand1 = operands;
                operand2 = "";
            } else {
                // If there are 2 operands, record them and clear the whitespaces
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
            // Record the tokens and push them to the current block of code
            tokens.push_back(ins);
            tokens.push_back(operand1);
            tokens.push_back(operand2);
            block.push_back(tokens);
            tokens.clear();
            // Update the current address in the memory
            address += 6;
            // If "int 20h" line is encountered, finish the parsing lines process
            if (!ins.compare("int") && !operand1.compare("20h") && !operand2.compare("")) {
                break;
            }
        }
    }
    // Record the last label
    blocks[curLabel] = block;
    // Now start the variable definition process
    while (getline(input, line)) {
        lineNum++;
        // Leave out enter characters and empty lines
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;
        // Make variable definition if the line is not empty, "code ends" line is also read there
        if (!operation::defineVar(line, lineNum, address, isSegment))
            return false;
    }
    // If "int 20h" or "code ends" line is not seen
    if (!isSegment)
        cout << "\"int 20h\" or \"code ends\" line can not be found.";
    return isSegment;
}

bool run() {

    /* Iterate through *labels* vector in order to call the corresponding block of code from *blocks*
    map and run it. */
    vector<string>::iterator it;
    for (it = labels.begin(); it != labels.end(); it++) {
        // Run the current block of code
        bool isRun = operation::process(blocks.at(*it), labelLines.at(*it));
        if (!isRun) {
            // If there is an error in the code
            if (nextLabel.empty())
                return false;
            // If the program actually ended
            else if (!nextLabel.compare("int20h"))
                return true;
            // If a jump instruction is made
            else
                it = find(labels.begin(), labels.end(), nextLabel) - 1;
        }
    }
    return true;
}

void printFinalState() {
    cout << endl;
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