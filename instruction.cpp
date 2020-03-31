//
//  instruction.cpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//
#include <iostream>

#include "instruction.hpp"
#include "variables.hpp"

namespace instruction {

    bool mov_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        reg1 = reg2;
        return true;
    }

    bool mov_reg16_wadd(unsigned short &reg, int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        reg = (1 << 8) * memory[address + 1] + memory[address];
        return true;
    }

    bool mov_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 16))
            return false;
        reg = (unsigned short) num;
        return true;
    }

    bool mov_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        reg1 = reg2;
        return true;
    }

    bool mov_reg8_badd(unsigned char &reg, int &address) {
        if (address >= (1 << 16))
            return false;
        reg = memory[address];
        return true;
    }

    bool mov_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 8))
            return false;
        reg = (unsigned char) num;
        return true;
    }

    bool mov_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned char high = reg / (1 << 8);
        unsigned char low = reg % (1 << 8);
        memory[address] = low;
        memory[address + 1] = high;
        return true;
    }

    bool mov_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 16))
            return false;
        unsigned char high = num / (1 << 8);
        unsigned char low = num % (1 << 8);
        memory[address] = low;
        memory[address + 1] = high;
        return true;
    }

    bool mov_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        memory[address] = reg;
        return true;
    }

    bool mov_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 8))
            return false;
        memory[address] = (unsigned char) num;
        return true;
    }

    bool operand1HighBit;
    bool operand2HighBit;
    char operand1LastHex;
    char resultLastHex;

    bool add_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        operand1HighBit = reg1 / (1 << 15);
        operand1LastHex = reg1 % (1 << 4);
        operand2HighBit = reg2 / (1 << 15);
        int sum = reg1 + reg2;
        reg1 = sum % (1 << 16);
        zf = !reg1;
        cf = sum / (1 << 16);
        sf = reg1 / (1 << 15);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg1 % (1 << 4);
        af = operand1LastHex > resultLastHex;
        return true;
    }

    bool add_reg16_wadd(unsigned short &reg, int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        operand1HighBit = reg / (1 << 15);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 15);
        int sum = reg + operand2;
        reg = sum % (1 << 16);
        zf = !reg;
        cf = sum / (1 << 16);
        sf = reg / (1 << 15);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex > resultLastHex;
        return true;
    }

    bool add_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 16))
            return false;
        unsigned short operand2 = num;
        operand1HighBit = reg / (1 << 15);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 15);
        int sum = reg + operand2;
        reg = sum % (1 << 16);
        zf = !reg;
        cf = sum / (1 << 16);
        sf = reg / (1 << 15);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex > resultLastHex;
        return true;
    }

    bool add_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        operand1HighBit = reg1 / (1 << 7);
        operand1LastHex = reg1 % (1 << 4);
        operand2HighBit = reg2 / (1 << 7);
        int sum = reg1 + reg2;
        reg1 = sum % (1 << 8);
        zf = !reg1;
        cf = sum / (1 << 8);
        sf = reg1 / (1 << 7);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg1 % (1 << 4);
        af = operand1LastHex > resultLastHex;
        return true;
    }

    bool add_reg8_badd(unsigned char &reg, int &address) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand2 = memory[address];
        operand1HighBit = reg / (1 << 7);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 7);
        int sum = reg + operand2;
        reg = sum % (1 << 8);
        zf = !reg;
        cf = sum / (1 << 8);
        sf = reg / (1 << 7);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex > resultLastHex;
        return true;
    }

    bool add_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 8))
            return false;
        unsigned char operand2 = num;
        operand1HighBit = reg / (1 << 7);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 7);
        int sum = reg + operand2;
        reg = sum % (1 << 8);
        zf = !reg;
        cf = sum / (1 << 8);
        sf = reg / (1 << 7);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex > resultLastHex;
        return true;
    }

    bool add_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        operand1HighBit = operand1 / (1 << 15);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = reg / (1 << 15);
        int sum = operand1 + reg;
        operand1 = sum % (1 << 16);
        zf = !operand1;
        cf = sum / (1 << 16);
        sf = operand1 / (1 << 15);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex > resultLastHex;
        unsigned char high = operand1 / (1 << 8);
        unsigned char low = operand1 % (1 << 8);
        memory[address] = low;
        memory[address + 1] = high;
        return true;
    }

    bool add_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 16))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        unsigned short operand2 = num;
        operand1HighBit = operand1 / (1 << 15);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = operand2 / (1 << 15);
        int sum = operand1 + operand2;
        operand1 = sum % (1 << 16);
        zf = !operand1;
        cf = sum / (1 << 16);
        sf = operand1 / (1 << 15);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex > resultLastHex;
        unsigned char high = operand1 / (1 << 8);
        unsigned char low = operand1 % (1 << 8);
        memory[address] = low;
        memory[address + 1] = high;
        return true;
    }

    bool add_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        operand1HighBit = operand1 / (1 << 7);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = reg / (1 << 7);
        int sum = operand1 + reg;
        operand1 = sum % (1 << 8);
        zf = !operand1;
        cf = sum / (1 << 8);
        sf = operand1 / (1 << 7);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex > resultLastHex;
        memory[address] = operand1;
        return true;
    }

    bool add_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 8))
            return false;
        unsigned char operand1 = memory[address];
        unsigned char operand2 = num;
        operand1HighBit = operand1 / (1 << 7);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = operand2 / (1 << 7);
        int sum = operand1 + operand2;
        operand1 = sum % (1 << 8);
        zf = !operand1;
        cf = sum / (1 << 8);
        sf = operand1 / (1 << 7);
        of = (operand1HighBit == operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex > resultLastHex;
        memory[address] = operand1;
        return true;
    }

    bool sub_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        operand1HighBit = reg1 / (1 << 15);
        operand1LastHex = reg1 % (1 << 4);
        operand2HighBit = reg2 / (1 << 15);
        int sum = reg1 - reg2;
        reg1 = (unsigned short) (sum % (1 << 16));
        zf = !reg1;
        cf = sum < 0;
        sf = reg1 / (1 << 15);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg1 % (1 << 4);
        af = operand1LastHex < resultLastHex;
        return true;
    }

    bool sub_reg16_wadd(unsigned short &reg, int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        operand1HighBit = reg / (1 << 15);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 15);
        int sum = reg - operand2;
        reg = (unsigned short) (sum % (1 << 16));
        zf = !reg;
        cf = sum < 0;
        sf = reg / (1 << 15);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex < resultLastHex;
        return true;
    }

    bool sub_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 16))
            return false;
        unsigned short operand2 = num;
        operand1HighBit = reg / (1 << 15);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 15);
        int sum = reg - operand2;
        reg = (unsigned short) (sum % (1 << 16));
        zf = !reg;
        cf = sum < 0;
        sf = reg / (1 << 15);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex < resultLastHex;
        return true;
    }

    bool sub_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        operand1HighBit = reg1 / (1 << 7);
        operand1LastHex = reg1 % (1 << 4);
        operand2HighBit = reg2 / (1 << 7);
        int sum = reg1 - reg2;
        reg1 = (unsigned char) (sum % (1 << 8));
        zf = !reg1;
        cf = sum < 0;
        sf = reg1 / (1 << 7);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg1 % (1 << 4);
        af = operand1LastHex < resultLastHex;
        return true;
    }

    bool sub_reg8_badd(unsigned char &reg, int &address) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand2 = memory[address];
        operand1HighBit = reg / (1 << 7);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 7);
        int sum = reg - operand2;
        reg = (unsigned char) (sum % (1 << 8));
        zf = !reg;
        cf = sum < 0;
        sf = reg / (1 << 7);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex < resultLastHex;
        return true;
    }

    bool sub_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 8))
            return false;
        unsigned char operand2 = num;
        operand1HighBit = reg / (1 << 7);
        operand1LastHex = reg % (1 << 4);
        operand2HighBit = operand2 / (1 << 7);
        int sum = reg - operand2;
        reg = (unsigned char) (sum % (1 << 8));
        zf = !reg;
        cf = sum < 0;
        sf = reg / (1 << 7);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = reg % (1 << 4);
        af = operand1LastHex < resultLastHex;
        return true;
    }

    bool sub_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        operand1HighBit = operand1 / (1 << 15);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = reg / (1 << 15);
        int sum = operand1 - reg;
        operand1 = (unsigned short) (sum % (1 << 16));
        zf = !operand1;
        cf = sum < 0;
        sf = operand1 / (1 << 15);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex < resultLastHex;
        unsigned char high = operand1 / (1 << 8);
        unsigned char low = operand1 % (1 << 8);
        memory[address] = low;
        memory[address + 1] = high;
        return true;
    }

    bool sub_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 16))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        unsigned short operand2 = num;
        operand1HighBit = operand1 / (1 << 15);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = operand2 / (1 << 15);
        int sum = operand1 - operand2;
        operand1 = (unsigned short) (sum % (1 << 16));
        zf = !operand1;
        cf = sum < 0;
        sf = operand1 / (1 << 15);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex < resultLastHex;
        unsigned char high = operand1 / (1 << 8);
        unsigned char low = operand1 % (1 << 8);
        memory[address] = low;
        memory[address + 1] = high;
        return true;
    }

    bool sub_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        operand1HighBit = operand1 / (1 << 7);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = reg / (1 << 7);
        int sum = operand1 - reg;
        operand1 = (unsigned char) (sum % (1 << 8));
        zf = !operand1;
        cf = sum < 0;
        sf = operand1 / (1 << 7);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex < resultLastHex;
        memory[address] = operand1;
        return true;
    }

    bool sub_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 8))
            return false;
        unsigned char operand1 = memory[address];
        unsigned char operand2 = num;
        operand1HighBit = operand1 / (1 << 7);
        operand1LastHex = operand1 % (1 << 4);
        operand2HighBit = operand2 / (1 << 7);
        int sum = operand1 - operand2;
        operand1 = (unsigned char) (sum % (1 << 8));
        zf = !operand1;
        cf = sum < 0;
        sf = operand1 / (1 << 7);
        of = (operand1HighBit != operand2HighBit) && (sf != operand1HighBit);
        resultLastHex = operand1 % (1 << 4);
        af = operand1LastHex < resultLastHex;
        memory[address] = operand1;
        return true;
    }

    bool mul_reg16(unsigned short &reg) {
        unsigned int result = ax * reg;
        dx = result / (1 << 16);
        ax = result % (1 << 16);
        cf = dx;
        of = cf;
        return true;
    }

    bool mul_reg8(unsigned char &reg) {
        ax = al * reg;
        cf = ax / (1 << 8);
        of = cf;
        return true;
    }

    bool mul_wadd(int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        unsigned int result = ax * operand2;
        dx = result / (1 << 16);
        ax = result % (1 << 16);
        cf = dx;
        of = cf;
        return true;
    }

    bool mul_badd(int &address) {
        if (address >= (1 << 16))
            return false;
        ax = al * memory[address];
        cf = ax / (1 << 8);
        of = cf;
        return true;
    }

    bool div_reg16(unsigned short &reg) {
        if (!reg)
            return false;
        unsigned int operand1 = (1 << 16) * dx + ax;
        unsigned int result = operand1 / reg;
        if (result >= (1 << 16))
            return false;
        ax = (unsigned short) result;
        dx = operand1 % reg;
        return true;
    }

    bool div_reg8(unsigned char &reg) {
        if (!reg)
            return false;
        unsigned short result = ax / reg;
        if (result >= (1 << 8))
            return false;
        al = (unsigned char) result;
        ah = ax % reg;
        return true;
    }

    bool div_wadd(int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        if (!operand2)
            return false;
        unsigned int operand1 = (1 << 16) * dx + ax;
        unsigned int result = operand1 / operand2;
        if (result >= (1 << 16))
            return false;
        ax = (unsigned short) result;
        dx = operand1 % operand2;
        return true;
    }

    bool div_badd(int &address) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand2 = memory[address];
        if (!operand2)
            return false;
        unsigned short result = ax / operand2;
        if (result >= (1 << 8))
            return false;
        al = (unsigned char) result;
        ah = ax % operand2;
        return true;
    }

    bool xor_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        reg1 = reg1 ^ reg2;
        zf = !reg1;
        cf = false;
        sf = reg1 / (1 << 15);
        of = false;
        return true;
    }

    bool xor_reg16_wadd(unsigned short &reg, int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        reg = reg ^ operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 15);
        of = false;
        return true;
    }

    bool xor_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 16))
            return false;
        unsigned short operand2 = num;
        reg = reg ^ operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 15);
        of = false;
        return true;
    }

    bool xor_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        reg1 = reg1 ^ reg2;
        zf = !reg1;
        cf = false;
        sf = reg1 / (1 << 7);
        of = false;
        return true;
    }

    bool xor_reg8_badd(unsigned char &reg, int &address) {
        if (address >= (1 << 16))
            return false;
        reg = reg ^ memory[address];
        zf = !reg;
        cf = false;
        sf = reg / (1 << 7);
        of = false;
        return true;
    }

    bool xor_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 8))
            return false;
        unsigned char operand2 = num;
        reg = reg ^ operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 7);
        of = false;
        return true;
    }

    bool xor_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        operand1 = operand1 ^ reg;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 15);
        of = false;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool xor_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 16))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        unsigned short operand2 = num;
        operand1 = operand1 ^ operand2;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 15);
        of = false;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool xor_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        operand1 = operand1 ^ reg;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 7);
        of = false;
        memory[address] = operand1;
        return true;
    }

    bool xor_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 8))
            return false;
        unsigned char operand1 = memory[address];
        unsigned char operand2 = num;
        operand1 = operand1 ^ operand2;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 7);
        of = false;
        memory[address] = operand1;
        return true;
    }

    bool or_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        reg1 = reg1 | reg2;
        zf = !reg1;
        cf = false;
        sf = reg1 / (1 << 15);
        of = false;
        return true;
    }

    bool or_reg16_wadd(unsigned short &reg, int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        reg = reg | operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 15);
        of = false;
        return true;
    }

    bool or_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 16))
            return false;
        unsigned short operand2 = num;
        reg = reg | operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 15);
        of = false;
        return true;
    }

    bool or_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        reg1 = reg1 | reg2;
        zf = !reg1;
        cf = false;
        sf = reg1 / (1 << 7);
        of = false;
        return true;
    }

    bool or_reg8_badd(unsigned char &reg, int &address) {
        if (address >= (1 << 16))
            return false;
        reg = reg | memory[address];
        zf = !reg;
        cf = false;
        sf = reg / (1 << 7);
        of = false;
        return true;
    }

    bool or_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 8))
            return false;
        unsigned char operand2 = num;
        reg = reg | operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 7);
        of = false;
        return true;
    }

    bool or_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        operand1 = operand1 | reg;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 15);
        of = false;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool or_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 16))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        unsigned short operand2 = num;
        operand1 = operand1 | operand2;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 15);
        of = false;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool or_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        operand1 = operand1 | reg;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 7);
        of = false;
        memory[address] = operand1;
        return true;
    }

    bool or_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 8))
            return false;
        unsigned char operand1 = memory[address];
        unsigned char operand2 = num;
        operand1 = operand1 | operand2;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 7);
        of = false;
        memory[address] = operand1;
        return true;
    }

    bool and_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        reg1 = reg1 & reg2;
        zf = !reg1;
        cf = false;
        sf = reg1 / (1 << 15);
        of = false;
        return true;
    }

    bool and_reg16_wadd(unsigned short &reg, int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand2 = (1 << 8) * memory[address + 1] + memory[address];
        reg = reg & operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 15);
        of = false;
        return true;
    }

    bool and_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 16))
            return false;
        unsigned short operand2 = num;
        reg = reg & operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 15);
        of = false;
        return true;
    }

    bool and_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        reg1 = reg1 & reg2;
        zf = !reg1;
        cf = false;
        sf = reg1 / (1 << 7);
        of = false;
        return true;
    }

    bool and_reg8_badd(unsigned char &reg, int &address) {
        if (address >= (1 << 16))
            return false;
        reg = reg & memory[address];
        zf = !reg;
        cf = false;
        sf = reg / (1 << 7);
        of = false;
        return true;
    }

    bool and_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 8))
            return false;
        unsigned char operand2 = num;
        reg = reg & operand2;
        zf = !reg;
        cf = false;
        sf = reg / (1 << 7);
        of = false;
        return true;
    }

    bool and_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        operand1 = operand1 & reg;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 15);
        of = false;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool and_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 16))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        unsigned short operand2 = num;
        operand1 = operand1 & operand2;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 15);
        of = false;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool and_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        operand1 = operand1 & reg;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 7);
        of = false;
        memory[address] = operand1;
        return true;
    }

    bool and_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 8))
            return false;
        unsigned char operand1 = memory[address];
        unsigned char operand2 = num;
        operand1 = operand1 & operand2;
        zf = !operand1;
        cf = false;
        sf = operand1 / (1 << 7);
        of = false;
        memory[address] = operand1;
        return true;
    }

    bool not_reg16(unsigned short &reg) {
        reg = ~reg;
        return true;
    }

    bool not_reg8(unsigned char &reg) {
        reg = ~reg;
        return true;
    }

    bool not_wadd(int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        operand1 = ~operand1;
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool not_badd(int &address) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        operand1 = ~operand1;
        memory[address] = operand1;
        return true;
    }

    int shift;
    bool tempCf;

    bool rcl_reg16_cl(unsigned short &reg1, unsigned char &reg2) {
        shift = (reg2 & 31) % 17;
        while (shift) {
            tempCf = reg1 / (1 << 15);
            reg1 = (reg1 << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (reg2 == 1)
            of = cf ^ (reg1 / (1 << 15));
        return true;
    }

    bool rcl_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num % 17;
        while (shift) {
            tempCf = reg / (1 << 15);
            reg = (reg << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (num == 1)
            of = cf ^ (reg / (1 << 15));
        return true;
    }

    bool rcl_reg8_cl(unsigned char &reg1, unsigned char &reg2) {
        shift = (reg2 & 31) % 9;
        while (shift) {
            tempCf = reg1 / (1 << 7);
            reg1 = (reg1 << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (reg2 == 1)
            of = cf ^ (reg1 / (1 << 7));
        return true;
    }

    bool rcl_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num % 9;
        while (shift) {
            tempCf = reg / (1 << 7);
            reg = (reg << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (num == 1)
            of = cf ^ (reg / (1 << 7));
        return true;
    }

    bool rcl_wadd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = (reg & 31) % 17;
        while (shift) {
            tempCf = operand1 / (1 << 15);
            operand1 = (operand1 << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (reg == 1)
            of = cf ^ (operand1 / (1 << 15));
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool rcl_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 5))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = num % 17;
        while (shift) {
            tempCf = operand1 / (1 << 15);
            operand1 = (operand1 << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (num == 1)
            of = cf ^ (operand1 / (1 << 15));
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool rcl_badd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        shift = (reg & 31) % 9;
        while (shift) {
            tempCf = operand1 / (1 << 7);
            operand1 = (operand1 << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (reg == 1)
            of = cf ^ (operand1 / (1 << 7));
        memory[address] = operand1;
        return true;
    }

    bool rcl_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 5))
            return false;
        unsigned char operand1 = memory[address];
        shift = num % 9;
        while (shift) {
            tempCf = operand1 / (1 << 7);
            operand1 = (operand1 << 1) + cf;
            cf = tempCf;
            shift--;
        }
        if (num == 1)
            of = cf ^ (operand1 / (1 << 7));
        memory[address] = operand1;
        return true;
    }

    bool rcr_reg16_cl(unsigned short &reg1, unsigned char &reg2) {
        shift = (reg2 & 31) % 17;
        if (reg2 == 1)
            of = cf ^ (reg1 / (1 << 15));
        while (shift) {
            tempCf = reg1 % 2;
            reg1 = (reg1 >> 1) + (cf << 15);
            cf = tempCf;
            shift--;
        }
        return true;
    }

    bool rcr_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num % 17;
        if (num == 1)
            of = cf ^ (reg / (1 << 15));
        while (shift) {
            tempCf = reg % 2;
            reg = (reg >> 1) + (cf << 15);
            cf = tempCf;
            shift--;
        }
        return true;
    }

    bool rcr_reg8_cl(unsigned char &reg1, unsigned char &reg2) {
        shift = (reg2 & 31) % 9;
        if (reg2 == 1)
            of = cf ^ (reg1 / (1 << 7));
        while (shift) {
            tempCf = reg1 % 2;
            reg1 = (reg1 >> 1) + (cf << 7);
            cf = tempCf;
            shift--;
        }
        return true;
    }

    bool rcr_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num % 9;
        if (num == 1)
            of = cf ^ (reg / (1 << 7));
        while (shift) {
            tempCf = reg % 2;
            reg = (reg >> 1) + (cf << 7);
            cf = tempCf;
            shift--;
        }
        return true;
    }

    bool rcr_wadd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = (reg & 31) % 17;
        if (reg == 1)
            of = cf ^ (operand1 / (1 << 15));
        while (shift) {
            tempCf = operand1 % 2;
            operand1 = (operand1 >> 1) + (cf << 15);
            cf = tempCf;
            shift--;
        }
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool rcr_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 5))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = num % 17;
        if (num == 1)
            of = cf ^ (operand1 / (1 << 15));
        while (shift) {
            tempCf = operand1 % 2;
            operand1 = (operand1 >> 1) + (cf << 15);
            cf = tempCf;
            shift--;
        }
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool rcr_badd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        shift = (reg & 31) % 9;
        if (reg == 1)
            of = cf ^ (operand1 / (1 << 7));
        while (shift) {
            tempCf = operand1 % 2;
            operand1 = (operand1 >> 1) + (cf << 7);
            cf = tempCf;
            shift--;
        }
        memory[address] = operand1;
        return true;
    }

    bool rcr_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 5))
            return false;
        unsigned char operand1 = memory[address];
        shift = num % 9;
        if (num == 1)
            of = cf ^ (operand1 / (1 << 7));
        while (shift) {
            tempCf = operand1 % 2;
            operand1 = (operand1 >> 1) + (cf << 7);
            cf = tempCf;
            shift--;
        }
        memory[address] = operand1;
        return true;
    }

    bool shl_reg16_cl(unsigned short &reg1, unsigned char &reg2) {
        shift = reg2 & 31;
        while (shift) {
            cf = reg1 / (1 << 15);
            reg1 = reg1 << 1;
            shift--;
        }
        if (reg2 == 1)
            of = cf ^ (reg1 / (1 << 15));
        if (reg2) {
            zf = !reg1;
            sf = reg1 / (1 << 15);
        }
        return true;
    }

    bool shl_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num;
        while (shift) {
            cf = reg / (1 << 15);
            reg = reg << 1;
            shift--;
        }
        if (num == 1)
            of = cf ^ (reg / (1 << 15));
        if (num) {
            zf = !reg;
            sf = reg / (1 << 15);
        }
        return true;
    }

    bool shl_reg8_cl(unsigned char &reg1, unsigned char &reg2) {
        shift = reg2 & 31;
        while (shift) {
            cf = reg1 / (1 << 7);
            reg1 = reg1 << 1;
            shift--;
        }
        if (reg2 == 1)
            of = cf ^ (reg1 / (1 << 7));
        if (reg2) {
            zf = !reg1;
            sf = reg1 / (1 << 7);
        }
        return true;
    }

    bool shl_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num;
        while (shift) {
            cf = reg / (1 << 7);
            reg = reg << 1;
            shift--;
        }
        if (num == 1)
            of = cf ^ (reg / (1 << 7));
        if (num) {
            zf = !reg;
            sf = reg / (1 << 7);
        }
        return true;
    }

    bool shl_wadd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = reg & 31;
        while (shift) {
            cf = operand1 / (1 << 15);
            operand1 = operand1 << 1;
            shift--;
        }
        if (reg == 1)
            of = cf ^ (operand1 / (1 << 15));
        if (reg) {
            zf = !operand1;
            sf = operand1 / (1 << 15);
        }
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool shl_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 5))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = num;
        while (shift) {
            cf = operand1 / (1 << 15);
            operand1 = operand1 << 1;
            shift--;
        }
        if (num == 1)
            of = cf ^ (operand1 / (1 << 15));
        if (num) {
            zf = !operand1;
            sf = operand1 / (1 << 15);
        }
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool shl_badd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        shift = reg & 31;
        while (shift) {
            cf = operand1 / (1 << 7);
            operand1 = operand1 << 1;
            shift--;
        }
        if (reg == 1)
            of = cf ^ (operand1 / (1 << 7));
        if (reg) {
            zf = !operand1;
            sf = operand1 / (1 << 7);
        }
        memory[address] = operand1;
        return true;
    }

    bool shl_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 5))
            return false;
        unsigned char operand1 = memory[address];
        shift = num;
        while (shift) {
            cf = operand1 / (1 << 7);
            operand1 = operand1 << 1;
            shift--;
        }
        if (num == 1)
            of = cf ^ (operand1 / (1 << 7));
        if (num) {
            zf = !operand1;
            sf = operand1 / (1 << 7);
        }
        memory[address] = operand1;
        return true;
    }

    bool shr_reg16_cl(unsigned short &reg1, unsigned char &reg2) {
        shift = reg2 & 31;
        if (shift == 1)
            of = reg1 / (1 << 15);
        while (shift) {
            cf = reg1 % 2;
            reg1 = reg1 >> 1;
            shift--;
        }
        if (reg2) {
            zf = !reg1;
            sf = reg1 / (1 << 15);
        }
        return true;
    }

    bool shr_reg16_num(unsigned short &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num;
        if (shift == 1)
            of = reg / (1 << 15);
        while (shift) {
            cf = reg % 2;
            reg = reg >> 1;
            shift--;
        }
        if (num) {
            zf = !reg;
            sf = reg / (1 << 15);
        }
        return true;
    }

    bool shr_reg8_cl(unsigned char &reg1, unsigned char &reg2) {
        shift = reg2 & 31;
        if (shift == 1)
            of = reg1 / (1 << 7);
        while (shift) {
            cf = reg1 % 2;
            reg1 = reg1 >> 1;
            shift--;
        }
        if (reg2) {
            zf = !reg1;
            sf = reg1 / (1 << 7);
        }
        return true;
    }

    bool shr_reg8_num(unsigned char &reg, int &num) {
        if (num >= (1 << 5))
            return false;
        shift = num;
        if (shift == 1)
            of = reg / (1 << 7);
        while (shift) {
            cf = reg % 2;
            reg = reg >> 1;
            shift--;
        }
        if (num) {
            zf = !reg;
            sf = reg / (1 << 7);
        }
        return true;
    }

    bool shr_wadd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = reg & 31;
        if (shift == 1)
            of = operand1 / (1 << 15);
        while (shift) {
            cf = operand1 % 2;
            operand1 = operand1 >> 1;
            shift--;
        }
        if (reg) {
            zf = !operand1;
            sf = operand1 / (1 << 15);
        }
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool shr_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1 || num >= (1 << 5))
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        shift = num;
        if (shift == 1)
            of = operand1 / (1 << 15);
        while (shift) {
            cf = operand1 % 2;
            operand1 = operand1 >> 1;
            shift--;
        }
        if (num) {
            zf = !operand1;
            sf = operand1 / (1 << 15);
        }
        unsigned char low = operand1 % (1 << 8);
        unsigned char high = operand1 / (1 << 8);
        memory[address + 1] = high;
        memory[address] = low;
        return true;
    }

    bool shr_badd_cl(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        shift = reg & 31;
        if (shift == 1)
            of = operand1 / (1 << 7);
        while (shift) {
            cf = operand1 % 2;
            operand1 = operand1 >> 1;
            shift--;
        }
        if (reg) {
            zf = !operand1;
            sf = operand1 / (1 << 7);
        }
        memory[address] = operand1;
        return true;
    }

    bool shr_badd_num(int &address, int &num) {
        if (address >= (1 << 16) || num >= (1 << 5))
            return false;
        unsigned char operand1 = memory[address];
        shift = num;
        if (shift == 1)
            of = operand1 / (1 << 7);
        while (shift) {
            cf = operand1 % 2;
            operand1 = operand1 >> 1;
            shift--;
        }
        if (num) {
            zf = !operand1;
            sf = operand1 / (1 << 7);
        }
        memory[address] = operand1;
        return true;
    }

    bool push_reg16(unsigned short &reg) {
        unsigned char low = reg % (1 << 8);
        unsigned char high = reg / (1 << 8);
        memory[sp + 1] = high;
        memory[sp] = low;
        sp -= 2;
        return true;
    }

    bool push_wadd(int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        memory[sp + 1] = memory[address + 1];
        memory[sp] = memory[address];
        sp -= 2;
        return true;
    }

    bool push_num(int &num) {
        if (num >= (1 << 16))
            return false;
        unsigned char low = num % (1 << 8);
        unsigned char high = num / (1 << 8);
        memory[sp + 1] = high;
        memory[sp] = low;
        sp -= 2;
        return true;
    }

    bool pop_reg16(unsigned short &reg) {
        if (sp >= 65534)
            return false;
        sp += 2;
        reg = (1 << 8) * memory[sp + 1] + memory[sp];
        return true;
    }

    bool pop_wadd(int &address) {
        if (sp >= 65534 || address >= (1 << 16) - 1)
            return false;
        sp += 2;
        memory[address + 1] = memory[sp + 1];
        memory[address] = memory[sp];
        return true;
    }

    bool cmp_reg16_reg16(unsigned short &reg1, unsigned short &reg2) {
        unsigned short operand1 = reg1;
        return sub_reg16_reg16(operand1, reg2);
    }

    bool cmp_reg16_wadd(unsigned short &reg, int &address) {
        unsigned short operand1 = reg;
        return sub_reg16_wadd(operand1, address);
    }

    bool cmp_reg16_num(unsigned short &reg, int &num) {
        unsigned short operand1 = reg;
        return sub_reg16_num(operand1, num);
    }

    bool cmp_reg8_reg8(unsigned char &reg1, unsigned char &reg2) {
        unsigned char operand1 = reg1;
        return sub_reg8_reg8(operand1, reg2);
    }

    bool cmp_reg8_badd(unsigned char &reg, int &address) {
        unsigned char operand1 = reg;
        return sub_reg8_badd(operand1, address);
    }

    bool cmp_reg8_num(unsigned char &reg, int &num) {
        unsigned char operand1 = reg;
        return sub_reg8_num(operand1, num);
    }

    bool cmp_wadd_reg16(int &address, unsigned short &reg) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        return sub_reg16_reg16(operand1, reg);
    }

    bool cmp_wadd_num(int &address, int &num) {
        if (address >= (1 << 16) - 1)
            return false;
        unsigned short operand1 = (1 << 8) * memory[address + 1] + memory[address];
        return sub_reg16_num(operand1, num);
    }

    bool cmp_badd_reg8(int &address, unsigned char &reg) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        return sub_reg8_reg8(operand1, reg);
    }

    bool cmp_badd_num(int &address, int &num) {
        if (address >= (1 << 16))
            return false;
        unsigned char operand1 = memory[address];
        return sub_reg8_num(operand1, num);
    }

    bool je(string &label) {
        if (zf) {
            nextLabel = label;
            return false;
        }
        return true;
    }

    bool jne(string &label) {
        if (!zf) {
            nextLabel = label;
            return false;
        }
        return true;
    }

    bool ja(string &label) {
        if (!zf && !cf) {
            nextLabel = label;
            return false;
        }
        return true;
    }

    bool jae(string &label) {
        if (!cf) {
            nextLabel = label;
            return false;
        }
        return true;
    }

    bool jb(string &label) {
        if (cf) {
            nextLabel = label;
            return false;
        }
        return true;
    }

    bool jbe(string &label) {
        if (zf || cf) {
            nextLabel = label;
            return false;
        }
        return true;
    }

    bool int21h() {
        if (ah == 1) {
            cin >> al;
            return true;
        } else if (ah == 2) {
            cout << dl;
            al = dl;
            return true;
        } else
            return false;
    }

    bool inc_reg16(unsigned short &reg) {
        tempCf = cf;
        int one = 1;
        add_reg16_num(reg, one);
        cf = tempCf;
        return true;
    }

    bool inc_reg8(unsigned char &reg) {
        tempCf = cf;
        int one = 1;
        add_reg8_num(reg, one);
        cf = tempCf;
        return true;
    }

    bool inc_wadd(int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        tempCf = cf;
        int one = 1;
        add_wadd_num(address, one);
        cf = tempCf;
        return true;
    }

    bool inc_badd(int &address) {
        if (address >= (1 << 16))
            return false;
        tempCf = cf;
        int one = 1;
        add_badd_num(address, one);
        cf = tempCf;
        return true;
    }

    bool dec_reg16(unsigned short &reg) {
        tempCf = cf;
        int one = 1;
        sub_reg16_num(reg, one);
        cf = tempCf;
        return true;
    }

    bool dec_reg8(unsigned char &reg) {
        tempCf = cf;
        int one = 1;
        sub_reg8_num(reg, one);
        cf = tempCf;
        return true;
    }

    bool dec_wadd(int &address) {
        if (address >= (1 << 16) - 1)
            return false;
        tempCf = cf;
        int one = 1;
        sub_wadd_num(address, one);
        cf = tempCf;
        return true;
    }

    bool dec_badd(int &address) {
        if (address >= (1 << 16))
            return false;
        tempCf = cf;
        int one = 1;
        sub_badd_num(address, one);
        cf = tempCf;
        return true;
    }
}