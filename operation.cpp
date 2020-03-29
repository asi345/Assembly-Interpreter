//
//  operation.cpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#include <iostream>
#include <algorithm>

#include "operation.hpp"
#include "variables.hpp"
#include "instruction.hpp"

namespace operation {

    bool defineVar(string& line, int& lineNum, int& address, bool& isEnd) {
        if (isEnd) {
            cout << "Syntax error at line " << lineNum << endl;
            return false;
        }
        string varName;
        string::iterator it;
        while (!line.empty() && line.back() == ' ')
            line.pop_back();
        int space = 0;
        while (line.size() != space && line.at(space) == ' ')
            space++;
        line = line.substr(space);
        space = line.find(' ');
        if (space == line.npos) {
            cout << "Syntax error at line " << lineNum << endl;
            return false;
        }
        varName = line.substr(0, space);
        for (it = varName.begin(); it != varName.end(); it++)
            *it = tolower(*it);
        string varRest = line.substr(space + 1);
        if (!isEnd && !varName.compare("code")) {
            string copy = varRest;
            for (it = copy.begin(); it != copy.end(); it++)
                *it = tolower(*it);
            if (!copy.compare("ends")) {
                isEnd = true;
                return true;
            }
        }
        space = 0;
        while (varRest.size() != space && varRest.at(space) == ' ')
            space++;
        varRest = varRest.substr(space);
        space = varRest.find(' ');
        if (space == varRest.npos) {
            cout << "Syntax error at line " << lineNum << endl;
            return false;
        }
        string typeDefine = varRest.substr(0, space);
        for (it = typeDefine.begin(); it != typeDefine.end(); it++)
            *it = tolower(*it);
        if (typeDefine.size() != 2 || typeDefine.front() != 'd') {
            cout << "Syntax error at line " << lineNum << endl;
            return false;
        }
        char type = typeDefine.back();
        string varValue = varRest.substr(space + 1);
        space = 0;
        while (varValue.size() != space && varValue.at(space) == ' ')
            space++;
        varValue = varValue.substr(space);
        unsigned char value;
        int tempValue;
        if (varValue.front() == '\'' && varValue.back() == '\'' && varValue.size() == 3) {
            value = varValue[1];
            addresses[varName] = address;
            memory[address] = value;
            if (type == 'b') {
                types[varName] = 'b';
                address++;
            } else if (type == 'w') {
                types[varName] = 'w';
                memory[address + 1] = 0;
                address += 2;
            } else {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
        } else {
            for (it = varValue.begin(); it != varValue.end(); it++)
                *it = tolower(*it);
            tempValue = hexToDec(varValue);
            if (tempValue == INT32_MAX)
                tempValue = decToDec(varValue);
            if (tempValue == INT32_MAX) {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
            addresses[varName] = address;
            if (type == 'b') {
                if (tempValue >= (1 << 8)) {
                    cout << "Syntax error at line " << lineNum << endl;
                    return false;
                }
                types[varName] = 'b';
                memory[address] = (unsigned char) tempValue;
                address++;
            } else if (type == 'w') {
                if (tempValue >= (1 << 16)) {
                    cout << "Syntax error at line " << lineNum << endl;
                    return false;
                }
                types[varName] = 'w';
                int rem = tempValue % (1 << 8);
                int div = tempValue / (1 << 8);
                memory[address] = (unsigned char) rem;
                memory[address + 1] = (unsigned char) div;
                address += 2;
            } else {
                cout << "Syntax error at line " << lineNum << endl;
                return false;
            }
        }
        return true;
    }

    int decToDec(string dec) {
        if (dec.empty())
            return INT32_MAX;
        if (dec.back() == 'd')
            dec.pop_back();
        if (dec.front() == '\'' && dec.back() == '\'' && dec.size() == 3)
            return dec.at(1);
        int result = 0, base = 1;
        string::reverse_iterator it;
        for (it = dec.rbegin(); it != dec.rend(); it++, base *= 10) {
            if (*it == '0')
                result += base * 0;
            else if (*it == '1')
                result += base * 1;
            else if (*it == '2')
                result += base * 2;
            else if (*it == '3')
                result += base * 3;
            else if (*it == '4')
                result += base * 4;
            else if (*it == '5')
                result += base * 5;
            else if (*it == '6')
                result += base * 6;
            else if (*it == '7')
                result += base * 7;
            else if (*it == '8')
                result += base * 8;
            else if (*it == '9')
                result += base * 9;
            else
                return INT32_MAX;
        }
        return result;
    }

    int hexToDec(string hex) {
        if (hex.empty() || hex.back() != 'h')
            return INT32_MAX;
        hex.pop_back();
        int result = 0, base = 1;
        string::reverse_iterator it;
        char first = hex.front();
        if (first >= 'a' && first <= 'f')
            return INT32_MAX;
        for (it = hex.rbegin(); it != hex.rend(); it++, base *= 16) {
            if (*it == '0')
                result += base * 0;
            else if (*it == '1')
                result += base * 1;
            else if (*it == '2')
                result += base * 2;
            else if (*it == '3')
                result += base * 3;
            else if (*it == '4')
                result += base * 4;
            else if (*it == '5')
                result += base * 5;
            else if (*it == '6')
                result += base * 6;
            else if (*it == '7')
                result += base * 7;
            else if (*it == '8')
                result += base * 8;
            else if (*it == '9')
                result += base * 9;
            else if (*it == 'a')
                result += base * 10;
            else if (*it == 'b')
                result += base * 11;
            else if (*it == 'c')
                result += base * 12;
            else if (*it == 'd')
                result += base * 13;
            else if (*it == 'e')
                result += base * 14;
            else if (*it == 'f')
                result += base * 15;
            else
                return INT32_MAX;
        }
        return result;
    }

    string decToHex(int dec) {
        return "";
    }

    bool isReg16(string& operand) {
        return !(reg16.find(operand) == reg16.end());
    }

    bool isReg8(string& operand) {
        return !(reg8.find(operand) == reg8.end());
    }

    void updateReg16(string reg) {
        if (!reg.compare("ax")) {
            ah = ax / (1 << 8);
            al = ax % (1 << 8);
        } else if (!reg.compare("bx")) {
            bh = bx / (1 << 8);
            bl = bx % (1 << 8);
        } else if (!reg.compare("cx")) {
            ch = cx / (1 << 8);
            cl = cx % (1 << 8);
        } else if (!reg.compare("dx")) {
            dh = dx / (1 << 8);
            dl = dx % (1 << 8);
        }
    }

    void updateReg8(string reg) {
        if (reg.front() == 'a')
            ax = al + (1 << 8) * ah;
        else if (reg.front() == 'b')
            bx = bl + (1 << 8) * bh;
        else if (reg.front() == 'c')
            cx = cl + (1 << 8) * ch;
        else if (reg.front() == 'd')
            dx = dl + (1 << 8) * dh;
    }

    pair<int, char> getAddress(string& operand) {
        if (operand.empty())
            return make_pair(0, '!');
        int address;
        char type = operand.front();
        unordered_map<string, char>::iterator it = types.find(operand);
        if (it != types.end()) {
            type = types.at(operand);
            address = addresses.at(operand);
            return make_pair(address, type);
        }
        if (type != 'w' && type != 'b')
            return make_pair (0, '!');
        int space = operand.find(' ');
        if (space != operand.npos) {
            string typer = operand.substr(0, space);
            if (!typer.compare("w") || !typer.compare("word") || !typer.compare("b") || !typer.compare("byte")) {
                string varName = operand.substr(space);
                space = 0;
                while (space != varName.size() && varName.at(space) == ' ')
                    space++;
                varName = varName.substr(space);
                it = types.find(varName);
                if (it != types.end()) {
                    address = addresses.at(varName);
                    return make_pair(address, type);
                }
            }
        }
        space = 1;
        while (space != operand.size() && operand.at(space) == ' ')
            space++;
        string addressStr = operand.substr(space);
        if (addressStr.front() != '[' || addressStr.back() != ']')
            return make_pair(0, '!');
        addressStr = addressStr.substr(1, addressStr.size() - 2);
        space = 0;
        while (space != addressStr.size() && addressStr.at(space) == ' ')
            space++;
        addressStr = addressStr.substr(space);
        while (!addressStr.empty() && addressStr.back() == ' ')
            addressStr.pop_back();
        if (isReg16(addressStr)) {
            address = *reg16Values.at(addressStr);
            return make_pair(address, type);
        } else if (isReg8(addressStr)) {
            address = *reg8Values.at(addressStr);
            return make_pair(address, type);
        } else {
            address = hexToDec(addressStr);
            if (address == INT32_MAX)
                address = decToDec(addressStr);
            if (address == INT32_MAX)
                return make_pair(0, '!');
            return make_pair(address, type);
        }
    }

    bool process(vector<string>& tokens, int lineNum) {
        string ins = tokens[0];
        string operand1 = tokens[1];
        string operand2 = tokens[2];
        nextLabel = "";
        bool isValid = false;
        if (ins.empty() && operand1.empty() && operand2.empty())
            return true;
        pair<int, char> pair1 = getAddress(operand1);
        int address1 = pair1.first;
        char type1 = pair1.second;
        pair<int, char> pair2 = getAddress(operand2);
        int address2 = pair2.first;
        char type2 = pair2.second;
        int num1 = hexToDec(operand1);
        if (num1 == INT32_MAX)
            num1 = decToDec(operand1);
        if (num1 == INT32_MAX) {
            int space = operand1.find(' ');
            string isOffset = operand1.substr(0, space);
            if (space != operand1.npos && !isOffset.compare("offset")) {
                string varName = operand1.substr(space + 1);
                int space = 0;
                while (space != varName.size() && varName.at(space) == ' ')
                    space++;
                varName = varName.substr(space);
                try {
                    num1 = addresses.at(varName);
                } catch (exception &e) {
                    num1 = INT32_MAX;
                }
            }
        }
        int num2 = hexToDec(operand2);
        if (num2 == INT32_MAX)
            num2 = decToDec(operand2);
        if (num2 == INT32_MAX) {
            int space = operand2.find(' ');
            string isOffset = operand2.substr(0, space);
            if (space != operand2.npos && !isOffset.compare("offset")) {
                string varName = operand2.substr(space + 1);
                int space = 0;
                while (space != varName.size() && varName.at(space) == ' ')
                    space++;
                varName = varName.substr(space);
                try {
                    num2 = addresses.at(varName);
                } catch (exception& e) {
                    num2 = INT32_MAX;
                }
            }
        }
        if (!ins.compare("mov")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::mov_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::mov_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::mov_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::mov_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::mov_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::mov_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::mov_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::mov_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::mov_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::mov_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("add")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::add_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::add_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::add_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::add_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::add_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::add_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::add_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::add_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::add_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::add_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("sub")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::sub_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::sub_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::sub_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::sub_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::sub_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::sub_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::sub_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::sub_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::sub_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::sub_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("mul")) {
            if (!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1)) {
                isValid = instruction::mul_reg16(*reg16Values.at(operand1));
                updateReg16("dx");
                updateReg16("ax");
            } else if (isReg8(operand1)) {
                isValid = instruction::mul_reg8(*reg8Values.at(operand1));
                updateReg16("ax");
            } else if (type1 == 'w') {
                isValid = instruction::mul_wadd(address1);
                updateReg16("dx");
                updateReg16("ax");
            } else if (type1 == 'b') {
                isValid = instruction::mul_badd(address1);
                updateReg16("ax");
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("div")) {
            if (!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1)) {
                isValid = instruction::div_reg16(*reg16Values.at(operand1));
                updateReg16("dx");
                updateReg16("ax");
            } else if (isReg8(operand1)) {
                isValid = instruction::div_reg8(*reg8Values.at(operand1));
                updateReg8("al");
                updateReg8("ah");
            } else if (type1 == 'w') {
                isValid = instruction::div_wadd(address1);
                updateReg16("dx");
                updateReg16("ax");
            } else if (type1 == 'b') {
                isValid = instruction::div_badd(address1);
                updateReg8("al");
                updateReg8("ah");
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("xor")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::xor_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::xor_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::xor_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::xor_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::xor_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::xor_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::xor_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::xor_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::xor_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::xor_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("or")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::or_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::or_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::or_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::or_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::or_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::or_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::or_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::or_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::or_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::or_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("and")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::and_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::and_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::and_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::and_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::and_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::and_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::and_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::and_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::and_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::and_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("not")) {
            if (!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1)) {
                isValid = instruction::not_reg16(*reg16Values.at(operand1));
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                isValid = instruction::not_reg8(*reg8Values.at(operand1));
                updateReg8(operand1);
            } else if (type1 == 'w') {
                isValid = instruction::not_wadd(address1);
            } else if (type1 == 'b') {
                isValid = instruction::not_badd(address1);
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("rcl")) {
            if (isReg16(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcl_reg16_cl(*reg16Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcl_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcl_reg8_cl(*reg8Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcl_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcl_wadd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcl_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcl_badd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcl_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("rcr")) {
            if (isReg16(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcr_reg16_cl(*reg16Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcr_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcr_reg8_cl(*reg8Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcr_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcr_wadd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcr_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (!operand2.compare("cl"))
                    isValid = instruction::rcr_badd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::rcr_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("shl")) {
            if (isReg16(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::shl_reg16_cl(*reg16Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shl_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::shl_reg8_cl(*reg8Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shl_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (!operand2.compare("cl"))
                    isValid = instruction::shl_wadd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shl_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (!operand2.compare("cl"))
                    isValid = instruction::shl_badd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shl_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("shr")) {
            if (isReg16(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::shr_reg16_cl(*reg16Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shr_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                if (!operand2.compare("cl"))
                    isValid = instruction::shr_reg8_cl(*reg8Values.at(operand1), cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shr_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                updateReg8(operand1);
            } else if (type1 == 'w') {
                if (!operand2.compare("cl"))
                    isValid = instruction::shr_wadd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shr_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (!operand2.compare("cl"))
                    isValid = instruction::shr_badd_cl(address1, cl);
                else if (num2 != INT32_MAX)
                    isValid = instruction::shr_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("push")) {
            if (!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1))
                isValid = instruction::push_reg16(*reg16Values.at(operand1));
            else if (type1 == 'w')
                isValid = instruction::push_wadd(address1);
            else if (num1 != INT32_MAX)
                isValid = instruction::push_num(num1);
            else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("pop")) {
            if (!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1)) {
                isValid = instruction::pop_reg16(*reg16Values.at(operand1));
                updateReg16(operand1);
            } else if (type1 == 'w')
                isValid = instruction::pop_wadd(address1);
            else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("cmp")) {
            if (isReg16(operand1)) {
                if (isReg16(operand2))
                    isValid = instruction::cmp_reg16_reg16(*reg16Values.at(operand1), *reg16Values.at(operand2));
                else if (type2 == 'w')
                    isValid = instruction::cmp_reg16_wadd(*reg16Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::cmp_reg16_num(*reg16Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (isReg8(operand1)) {
                if (isReg8(operand2))
                    isValid = instruction::cmp_reg8_reg8(*reg8Values.at(operand1), *reg8Values.at(operand2));
                else if (type2 == 'b')
                    isValid = instruction::cmp_reg8_badd(*reg8Values.at(operand1), address2);
                else if (num2 != INT32_MAX)
                    isValid = instruction::cmp_reg8_num(*reg8Values.at(operand1), num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'w') {
                if (isReg16(operand2))
                    isValid = instruction::cmp_wadd_reg16(address1, *reg16Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::cmp_wadd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else if (type1 == 'b') {
                if (isReg8(operand2))
                    isValid = instruction::cmp_badd_reg8(address1, *reg8Values.at(operand2));
                else if (num2 != INT32_MAX)
                    isValid = instruction::cmp_badd_num(address1, num2);
                else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("jmp")) {
            if (!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            nextLabel = operand1;
            isValid = false;
            if (find(labels.begin(), labels.end(), nextLabel) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("jz") || !ins.compare("je")) {
            if (!operand2.empty() || find(labels.begin(), labels.end(), operand1) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            isValid = instruction::je(operand1);
        } else if (!ins.compare("jnz") || !ins.compare("jne")) {
            if (!operand2.empty() || find(labels.begin(), labels.end(), operand1) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            isValid = instruction::jne(operand1);
        } else if (!ins.compare("ja") || !ins.compare("jnbe")) {
            if (!operand2.empty() || find(labels.begin(), labels.end(), operand1) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            isValid = instruction::ja(operand1);
        } else if (!ins.compare("jae") || !ins.compare("jnb") || !ins.compare("jnc")) {
            if (!operand2.empty() || find(labels.begin(), labels.end(), operand1) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            isValid = instruction::jae(operand1);
        } else if (!ins.compare("jb") || !ins.compare("jnae") || !ins.compare("jc")) {
            if (!operand2.empty() || find(labels.begin(), labels.end(), operand1) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            isValid = instruction::jb(operand1);
        } else if (!ins.compare("jbe") || !ins.compare("jna")) {
            if (!operand2.empty() || find(labels.begin(), labels.end(), operand1) == labels.end()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            isValid = instruction::jbe(operand1);
        } else if (!ins.compare("inc")) {
            if(!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1)) {
                isValid = instruction::inc_reg16(*reg16Values.at(operand1));
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                isValid = instruction::inc_reg8(*reg8Values.at(operand1));
                updateReg8(operand1);
            } else if (type1 == 'w') {
                isValid = instruction::inc_wadd(address1);
            } else if (type1 == 'b') {
                isValid = instruction::inc_badd(address1);
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("dec")) {
            if(!operand2.empty()) {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
            if (isReg16(operand1)) {
                isValid = instruction::dec_reg16(*reg16Values.at(operand1));
                updateReg16(operand1);
            } else if (isReg8(operand1)) {
                isValid = instruction::dec_reg8(*reg8Values.at(operand1));
                updateReg8(operand1);
            } else if (type1 == 'w') {
                isValid = instruction::dec_wadd(address1);
            } else if (type1 == 'b') {
                isValid = instruction::dec_badd(address1);
            } else {
                cout << "Error at line " << lineNum << endl;
                return false;
            }
        } else if (!ins.compare("int")) {
                if (!operand2.empty()) {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
                if (num1 == 32) {
                    nextLabel = "int20h";
                    return false;
                } else if (num1 == 33) {
                    isValid = instruction::int21h();
                    updateReg8("al");
                } else {
                    cout << "Error at line " << lineNum << endl;
                    return false;
                }
            }
        if (!isValid && nextLabel.empty())
            cout << "Error at line " << lineNum << endl;
        return isValid;
    }

    bool process(vector<vector<string> >& block, int lineNum) {
        for (int i = 0; i < block.size(); i++) {
            bool isProcessed = process(block[i], lineNum + i + 1);
            if (!isProcessed)
                return false;
        }
        return true;
    }

}