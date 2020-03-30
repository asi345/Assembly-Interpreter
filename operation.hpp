//
//  operation.hpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#ifndef operation_hpp
#define operation_hpp

#include <iostream>

#include <string>
#include <vector>

using namespace std;

/* Contains useful functions that does the necessary hard works. They help string parsing and decide which
 instruction will be executed by returning specific values or calling instruction functions from the
 *instruction* namespace. This namespace is a bridge between strings that are read from the file and the
 process of applying instructions.
*/
namespace operation {

/* Parses the given line and handles a variable definition made in that line of the Assembly code. Returns
 true if the operation is successful.
    * line -> line to be parsed
    * lineNum -> parsed line's number
    * address -> memory address where the new defined variable will be kept
    * isEnd -> boolean to control whether the "code ends" line is encountered
*/
    bool defineVar(string& line, int& lineNum, int& address, bool& isEnd);

/* Returns the integer equivalent to the decimal value in the string parameter. It can also read chars when
 given as like 'a'. Returns *INT32_MAX* if the given string does not correspond to a decimal.
    * dec -> contains string equivalent of the number to be turned into integer
 */
    int decToDec(string dec);

/* Returns the integer equivalent to the hex value in the string parameter. Returns *INT32_MAX* if the given
 string does not correspond to a hex
    * hex -> contains string equivalent of the number to be turned into integer
*/
    int hexToDec(string hex);

/* Returns true if the string parameter corresponds to a 16 bit register.
    * operand -> operand to be checked if it is a 16 bit register
*/
    bool isReg16(string& operand);

/* Returns true if the string parameter corresponds to a 8 bit register.
    * operand -> operand to be checked if it is a 8 bit register
*/
    bool isReg8(string& operand);

/* Updates the values of the 8 bit registers according to the values in the 16 bit registers.
    * reg -> 16 bit register whose 8 bit parts are to be updated
*/
    void updateReg16(string reg);

/* Updates the values of the 16 bit registers according to the values in the 8 bit registers.
    * reg -> 8 bit register which the 16 bit register it is in to be updated
*/
    void updateReg8(string reg);

/* Returns the address value in integer and the type of the variable in that address if the given string
 parameter corresponds to a memory address. Returns *pair<0, '!'>* if the string does not correspond to an
 address. Memory accesses made with just variable name are also done here.
    * operand -> operand to be parsed to check if it does a memory access
*/
    pair<int, char> getAddress(string& operand);

/* Parses the given line and applies the appropriate instruction in the system according to that line.
 The code actually runs in this function and therefore the most essential part of the interpretation is done
 here. Returns true if the line is processed successfully.
    * tokens -> vector with 3 elements : instruction, operand1 and operand2
    * lineNum -> parsed line's number
 */
    bool process(vector<string>& tokens, int lineNum);

/* Parses the given block of code and separates them into lines. Then calls *process* function above for
 each line. Returns true if all the lines the block are processed successfully.
    * block -> block of code written under a label
    * lineNum -> line number where the block of code starts, actually line number of the label whose contents
are *block*
*/
    bool process(vector<vector<string> >& block, int lineNum);

}

#endif /* operation_hpp */