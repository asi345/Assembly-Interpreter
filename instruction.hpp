//
//  instruction.hpp
//  Assembly Interpreter
//
//  Created by Ata İnan on 17.03.2020.
//  Copyright © 2020 Ata İnan. All rights reserved.
//

#ifndef instruction_hpp
#define instruction_hpp

#include <iostream>
#include <string>

using namespace std;

/* Contains the functions that actually performs the instructions given in the Assembly code. These
 functions make use of *operation* namespace to determine which function to run and what parameters
 to use. They also do not check for syntax errors, that job is done at the *operation* namespace
 functions. They only check for overflow errors.
*/
namespace instruction {

    // Performs the "mov" instruction on 16 bit registers.
    bool mov_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "mov" instruction from a word in memory into a 16 bit register.
    bool mov_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "mov" instruction from an immediate number into a 16 bit register.
    bool mov_reg16_num(unsigned short& reg, int& num);

    // Performs the "mov" instruction on 8 bit registers.
    bool mov_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "mov" instruction from a byte in memory into a 8 bit register.
    bool mov_reg8_badd(unsigned char& reg, int& address);

    // Performs the "mov" instruction from an immediate number into a 8 bit register.
    bool mov_reg8_num(unsigned char& reg, int& num);

    // Performs the "mov" instruction from a 16 bit register into a word in memory.
    bool mov_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "mov" instruction from an immediate number into a word in memory.
    bool mov_wadd_num(int& address, int& num);

    // Performs the "mov" instruction from a 8 bit register into a byte in memory.
    bool mov_badd_reg8(int& address, unsigned char& reg);

    // Performs the "mov" instruction from an immediate number into a byte in memory.
    bool mov_badd_num(int& address, int& num);

    // Performs the "add" instruction on 16 bit registers.
    bool add_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "add" instruction with a word in memory in a 16 bit register.
    bool add_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "add" instruction with an immediate number in a 16 bit register.
    bool add_reg16_num(unsigned short& reg, int& num);

    // Performs the "add" instruction on 8 bit registers.
    bool add_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "add" instruction with a byte in memory in a 8 bit register.
    bool add_reg8_badd(unsigned char& reg, int& address);

    // Performs the "add" instruction with an immediate number in a 8 bit register.
    bool add_reg8_num(unsigned char& reg, int& num);

    // Performs the "add" instruction with a 16 bit register in a word in memory.
    bool add_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "add" instruction with an immediate number in a word in memory.
    bool add_wadd_num(int& address, int& num);

    // Performs the "add" instruction with a 8 bit register in a byte in memory.
    bool add_badd_reg8(int& address, unsigned char& reg);

    // Performs the "add" instruction with an immediate number in a byte in memory.
    bool add_badd_num(int& address, int& num);

    // Performs the "sub" instruction on 16 bit registers.
    bool sub_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "sub" instruction with a word in memory in a 16 bit register.
    bool sub_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "sub" instruction with an immediate number in a 16 bit register.
    bool sub_reg16_num(unsigned short& reg, int& num);

    // Performs the "sub" instruction on 8 bit registers.
    bool sub_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "sub" instruction with a byte in memory in a 8 bit register.
    bool sub_reg8_badd(unsigned char& reg, int& address);

    // Performs the "sub" instruction with an immediate number in a 8 bit register.
    bool sub_reg8_num(unsigned char& reg, int& num);

    // Performs the "sub" instruction with a 16 bit register in a word in memory.
    bool sub_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "sub" instruction with an immediate number in a word in memory.
    bool sub_wadd_num(int& address, int& num);

    // Performs the "sub" instruction with a 8 bit register in a byte in memory.
    bool sub_badd_reg8(int& address, unsigned char& reg);

    // Performs the "sub" instruction with an immediate number in a byte in memory.
    bool sub_badd_num(int& address, int& num);

    // Performs the "mul" instruction with a 16 bit register.
    bool mul_reg16(unsigned short& reg);

    // Performs the "mul" instruction with a 8 bit register.
    bool mul_reg8(unsigned char& reg);

    // Performs the "mul" instruction with a word in memory.
    bool mul_wadd(int& address);

    // Performs the "mul" instruction with a byte in memory.
    bool mul_badd(int& address);

    // Performs the "div" instruction with a 16 bit register.
    bool div_reg16(unsigned short& reg);

    // Performs the "div" instruction with a 8 bit register.
    bool div_reg8(unsigned char& reg);

    // Performs the "div" instruction with a word in memory.
    bool div_wadd(int& address);

    // Performs the "div" instruction with a byte in memory.
    bool div_badd(int& address);

    // Performs the "xor" instruction on 16 bit registers.
    bool xor_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "xor" instruction with a word in memory in a 16 bit register.
    bool xor_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "xor" instruction with an immediate number in a 16 bit register.
    bool xor_reg16_num(unsigned short& reg, int& num);

    // Performs the "xor" instruction on 8 bit registers.
    bool xor_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "xor" instruction with a byte in memory in a 8 bit register.
    bool xor_reg8_badd(unsigned char& reg, int& address);

    // Performs the "xor" instruction with an immediate number in a 8 bit register.
    bool xor_reg8_num(unsigned char& reg, int& num);

    // Performs the "xor" instruction with a 16 bit register in a word in memory.
    bool xor_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "xor" instruction with an immediate number in a word in memory.
    bool xor_wadd_num(int& address, int& num);

    // Performs the "xor" instruction with a 8 bit register in a byte in memory.
    bool xor_badd_reg8(int& address, unsigned char& reg);

    // Performs the "xor" instruction with an immediate number in a byte in memory.
    bool xor_badd_num(int& address, int& num);

    // Performs the "or" instruction on 16 bit registers.
    bool or_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "or" instruction with a word in memory in a 16 bit register.
    bool or_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "or" instruction with an immediate number in a 16 bit register.
    bool or_reg16_num(unsigned short& reg, int& num);

    // Performs the "or" instruction on 8 bit registers.
    bool or_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "or" instruction with a byte in memory in a 8 bit register.
    bool or_reg8_badd(unsigned char& reg, int& address);

    // Performs the "or" instruction with an immediate number in a 8 bit register.
    bool or_reg8_num(unsigned char& reg, int& num);

    // Performs the "or" instruction with a 16 bit register in a word in memory.
    bool or_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "or" instruction with an immediate number in a word in memory.
    bool or_wadd_num(int& address, int& num);

    // Performs the "or" instruction with a 8 bit register in a byte in memory.
    bool or_badd_reg8(int& address, unsigned char& reg);

    // Performs the "or" instruction with an immediate number in a byte in memory.
    bool or_badd_num(int& address, int& num);

    // Performs the "and" instruction on 16 bit registers.
    bool and_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "and" instruction with a word in memory in a 16 bit register.
    bool and_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "and" instruction with an immediate number in a 16 bit register.
    bool and_reg16_num(unsigned short& reg, int& num);

    // Performs the "and" instruction on 8 bit registers.
    bool and_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "and" instruction with a byte in memory in a 8 bit register.
    bool and_reg8_badd(unsigned char& reg, int& address);

    // Performs the "and" instruction with an immediate number in a 8 bit register.
    bool and_reg8_num(unsigned char& reg, int& num);

    // Performs the "and" instruction with a 16 bit register in a word in memory.
    bool and_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "and" instruction with an immediate number in a word in memory.
    bool and_wadd_num(int& address, int& num);

    // Performs the "and" instruction with a 8 bit register in a byte in memory.
    bool and_badd_reg8(int& address, unsigned char& reg);

    // Performs the "and" instruction with an immediate number in a byte in memory.
    bool and_badd_num(int& address, int& num);

    // Performs the "not" instruction in a 16 bit register.
    bool not_reg16(unsigned short& reg);

    // Performs the "not" instruction in a 8 bit register.
    bool not_reg8(unsigned char& reg);

    // Performs the "not" instruction in a word in memory.
    bool not_wadd(int& address);

    // Performs the "not" instruction in a byte in memory.
    bool not_badd(int& address);

    // Performs the "rcl" instruction in a 16 bit register by the value in "cl".
    bool rcl_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    // Performs the "rcl" instruction in a 16 bit register by an immediate number.
    bool rcl_reg16_num(unsigned short& reg, int& num);

    // Performs the "rcl" instruction in a 8 bit register by the value in "cl".
    bool rcl_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    // Performs the "rcl" instruction in a 8 bit register by an immediate number.
    bool rcl_reg8_num(unsigned char& reg, int& num);

    // Performs the "rcl" instruction in a word in memory by the value in "cl".
    bool rcl_wadd_cl(int& address, unsigned char& reg);

    // Performs the "rcl" instruction in a word in memory by an immediate number.
    bool rcl_wadd_num(int& address, int& num);

    // Performs the "rcl" instruction in a byte in memory by the value in "cl".
    bool rcl_badd_cl(int& address, unsigned char& reg);

    // Performs the "rcl" instruction in a byte in memory by an immediate number.
    bool rcl_badd_num(int& address, int& num);

    // Performs the "rcr" instruction in a 16 bit register by the value in "cl".
    bool rcr_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    // Performs the "rcr" instruction in a 16 bit register by an immediate number.
    bool rcr_reg16_num(unsigned short& reg, int& num);

    // Performs the "rcr" instruction in a 8 bit register by the value in "cl".
    bool rcr_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    // Performs the "rcr" instruction in a 8 bit register by an immediate number.
    bool rcr_reg8_num(unsigned char& reg, int& num);

    // Performs the "rcr" instruction in a word in memory by the value in "cl".
    bool rcr_wadd_cl(int& address, unsigned char& reg);

    // Performs the "rcr" instruction in a word in memory by an immediate number.
    bool rcr_wadd_num(int& address, int& num);

    // Performs the "rcr" instruction in a byte in memory by the value in "cl".
    bool rcr_badd_cl(int& address, unsigned char& reg);

    // Performs the "rcr" instruction in a byte in memory by an immediate number.
    bool rcr_badd_num(int& address, int& num);

    // Performs the "shl" instruction in a 16 bit register by the value in "cl".
    bool shl_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    // Performs the "shl" instruction in a 16 bit register by an immediate number.
    bool shl_reg16_num(unsigned short& reg, int& num);

    // Performs the "shl" instruction in a 8 bit register by the value in "cl".
    bool shl_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    // Performs the "shl" instruction in a 8 bit register by an immediate number.
    bool shl_reg8_num(unsigned char& reg, int& num);

    // Performs the "shl" instruction in a word in memory by the value in "cl".
    bool shl_wadd_cl(int& address, unsigned char& reg);

    // Performs the "shl" instruction in a word in memory by an immediate number.
    bool shl_wadd_num(int& address, int& num);

    // Performs the "shl" instruction in a byte in memory by the value in "cl".
    bool shl_badd_cl(int& address, unsigned char& reg);

    // Performs the "shl" instruction in a byte in memory by an immediate number.
    bool shl_badd_num(int& address, int& num);

    // Performs the "shr" instruction in a 16 bit register by the value in "cl".
    bool shr_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    // Performs the "shr" instruction in a 16 bit register by an immediate number.
    bool shr_reg16_num(unsigned short& reg, int& num);

    // Performs the "shr" instruction in a 8 bit register by the value in "cl".
    bool shr_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    // Performs the "shr" instruction in a 8 bit register by an immediate number.
    bool shr_reg8_num(unsigned char& reg, int& num);

    // Performs the "shr" instruction in a word in memory by the value in "cl".
    bool shr_wadd_cl(int& address, unsigned char& reg);

    // Performs the "shr" instruction in a word in memory by an immediate number.
    bool shr_wadd_num(int& address, int& num);

    // Performs the "shr" instruction in a byte in memory by the value in "cl".
    bool shr_badd_cl(int& address, unsigned char& reg);

    // Performs the "shr" instruction in a byte in memory by an immediate number.
    bool shr_badd_num(int& address, int& num);

    // Performs the "push" instruction from a 16 bit register.
    bool push_reg16(unsigned short& reg);

    // Performs the "push" instruction from a word in memory.
    bool push_wadd(int& address);

    // Performs the "push" instruction from a immediate number.
    bool push_num(int& num);

    // Performs the "pop" instruction into a 16 bit register.
    bool pop_reg16(unsigned short& reg);

    // Performs the "pop" instruction into a word in memory
    bool pop_wadd(int& address);

    // Performs the "cmp" instruction on 16 bit registers.
    bool cmp_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    // Performs the "cmp" instruction with a word in memory in a 16 bit register.
    bool cmp_reg16_wadd(unsigned short& reg, int& address);

    // Performs the "cmp" instruction with an immediate number in a 16 bit register.
    bool cmp_reg16_num(unsigned short& reg, int& num);

    // Performs the "cmp" instruction on 8 bit registers.
    bool cmp_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    // Performs the "cmp" instruction with a byte in memory in a 8 bit register.
    bool cmp_reg8_badd(unsigned char& reg, int& address);

    // Performs the "cmp" instruction with an immediate number in a 8 bit register.
    bool cmp_reg8_num(unsigned char& reg, int& num);

    // Performs the "cmp" instruction with a 16 bit register in a word in memory.
    bool cmp_wadd_reg16(int& address, unsigned short& reg);

    // Performs the "cmp" instruction with an immediate number in a word in memory.
    bool cmp_wadd_num(int& address, int& num);

    // Performs the "cmp" instruction with a 8 bit register in a byte in memory.
    bool cmp_badd_reg8(int& address, unsigned char& reg);

    // Performs the "cmp" instruction with an immediate number in a byte in memory.
    bool cmp_badd_num(int& address, int& num);

    // Performs the "jz" and "je" instructions
    bool je(string& label);

    // Performs the "jnz" and "jne" instructions
    bool jne(string& label);

    // Performs the "ja" and "jnbe" instructions
    bool ja(string& label);

    // Performs the "jae", "jnb" and "jnc" instructions
    bool jae(string& label);

    // Performs the "jb", "jnae" and "jc" instructions
    bool jb(string& label);

    // Performs the "jbe" and "jna" instructions
    bool jbe(string& label);

    // Performs the "inc" instruction in a 16 bit register.
    bool inc_reg16(unsigned short& reg);

    // Performs the "inc" instruction in a 8 bit register.
    bool inc_reg8(unsigned char& reg);

    // Performs the "inc" instruction in a word in memory.
    bool inc_wadd(int& address);

    // Performs the "inc" instruction in a byte in memory.
    bool inc_badd(int& address);

    // Performs the "dec" instruction in a 16 bit register.
    bool dec_reg16(unsigned short& reg);

    // Performs the "dec" instruction in a 18bit register.
    bool dec_reg8(unsigned char& reg);

    // Performs the "dec" instruction in a word in memory.
    bool dec_wadd(int& address);

    // Performs the "dec" instruction in a byte in memory.
    bool dec_badd(int& address);

    // Performs the "int" instruction
    bool int21h();
}

#endif /* instruction_hpp */