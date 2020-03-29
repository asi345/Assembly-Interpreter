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
 to use. They also do not check for errors, that job is done at the *operation* namespace functions.
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

    bool add_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    bool add_reg16_wadd(unsigned short& reg, int& address);

    bool add_reg16_num(unsigned short& reg, int& num);

    bool add_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    bool add_reg8_badd(unsigned char& reg, int& address);

    bool add_reg8_num(unsigned char& reg, int& num);

    bool add_wadd_reg16(int& address, unsigned short& reg);

    bool add_wadd_num(int& address, int& num);

    bool add_badd_reg8(int& address, unsigned char& reg);

    bool add_badd_num(int& address, int& num);

    bool sub_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    bool sub_reg16_wadd(unsigned short& reg, int& address);

    bool sub_reg16_num(unsigned short& reg, int& num);

    bool sub_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    bool sub_reg8_badd(unsigned char& reg, int& address);

    bool sub_reg8_num(unsigned char& reg, int& num);

    bool sub_wadd_reg16(int& address, unsigned short& reg);

    bool sub_wadd_num(int& address, int& num);

    bool sub_badd_reg8(int& address, unsigned char& reg);

    bool sub_badd_num(int& address, int& num);

    bool mul_reg16(unsigned short& reg);

    bool mul_reg8(unsigned char& reg);

    bool mul_wadd(int& address);

    bool mul_badd(int& address);

    bool div_reg16(unsigned short& reg);

    bool div_reg8(unsigned char& reg);

    bool div_wadd(int& address);

    bool div_badd(int& address);

    bool xor_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    bool xor_reg16_wadd(unsigned short& reg, int& address);

    bool xor_reg16_num(unsigned short& reg, int& num);

    bool xor_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    bool xor_reg8_badd(unsigned char& reg, int& address);

    bool xor_reg8_num(unsigned char& reg, int& num);

    bool xor_wadd_reg16(int& address, unsigned short& reg);

    bool xor_wadd_num(int& address, int& num);

    bool xor_badd_reg8(int& address, unsigned char& reg);

    bool xor_badd_num(int& address, int& num);

    bool or_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    bool or_reg16_wadd(unsigned short& reg, int& address);

    bool or_reg16_num(unsigned short& reg, int& num);

    bool or_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    bool or_reg8_badd(unsigned char& reg, int& address);

    bool or_reg8_num(unsigned char& reg, int& num);

    bool or_wadd_reg16(int& address, unsigned short& reg);

    bool or_wadd_num(int& address, int& num);

    bool or_badd_reg8(int& address, unsigned char& reg);

    bool or_badd_num(int& address, int& num);

    bool and_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    bool and_reg16_wadd(unsigned short& reg, int& address);

    bool and_reg16_num(unsigned short& reg, int& num);

    bool and_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    bool and_reg8_badd(unsigned char& reg, int& address);

    bool and_reg8_num(unsigned char& reg, int& num);

    bool and_wadd_reg16(int& address, unsigned short& reg);

    bool and_wadd_num(int& address, int& num);

    bool and_badd_reg8(int& address, unsigned char& reg);

    bool and_badd_num(int& address, int& num);

    bool not_reg16(unsigned short& reg);

    bool not_reg8(unsigned char& reg);

    bool not_wadd(int& address);

    bool not_badd(int& address);

    bool rcl_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    bool rcl_reg16_num(unsigned short& reg, int& num);

    bool rcl_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    bool rcl_reg8_num(unsigned char& reg, int& num);

    bool rcl_wadd_cl(int& address, unsigned char& reg);

    bool rcl_wadd_num(int& address, int& num);

    bool rcl_badd_cl(int& address, unsigned char& reg);

    bool rcl_badd_num(int& address, int& num);

    bool rcr_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    bool rcr_reg16_num(unsigned short& reg, int& num);

    bool rcr_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    bool rcr_reg8_num(unsigned char& reg, int& num);

    bool rcr_wadd_cl(int& address, unsigned char& reg);

    bool rcr_wadd_num(int& address, int& num);

    bool rcr_badd_cl(int& address, unsigned char& reg);

    bool rcr_badd_num(int& address, int& num);

    bool shl_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    bool shl_reg16_num(unsigned short& reg, int& num);

    bool shl_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    bool shl_reg8_num(unsigned char& reg, int& num);

    bool shl_wadd_cl(int& address, unsigned char& reg);

    bool shl_wadd_num(int& address, int& num);

    bool shl_badd_cl(int& address, unsigned char& reg);

    bool shl_badd_num(int& address, int& num);

    bool shr_reg16_cl(unsigned short& reg1, unsigned char& reg2);

    bool shr_reg16_num(unsigned short& reg, int& num);

    bool shr_reg8_cl(unsigned char& reg1, unsigned char& reg2);

    bool shr_reg8_num(unsigned char& reg, int& num);

    bool shr_wadd_cl(int& address, unsigned char& reg);

    bool shr_wadd_num(int& address, int& num);

    bool shr_badd_cl(int& address, unsigned char& reg);

    bool shr_badd_num(int& address, int& num);

    bool push_reg16(unsigned short& reg);

    bool push_wadd(int& address);

    bool push_num(int& num);

    bool pop_reg16(unsigned short& reg);

    bool pop_wadd(int& address);

    bool cmp_reg16_reg16(unsigned short& reg1, unsigned short& reg2);

    bool cmp_reg16_wadd(unsigned short& reg, int& address);

    bool cmp_reg16_num(unsigned short& reg, int& num);

    bool cmp_reg8_reg8(unsigned char& reg1, unsigned char& reg2);

    bool cmp_reg8_badd(unsigned char& reg, int& address);

    bool cmp_reg8_num(unsigned char& reg, int& num);

    bool cmp_wadd_reg16(int& address, unsigned short& reg);

    bool cmp_wadd_num(int& address, int& num);

    bool cmp_badd_reg8(int& address, unsigned char& reg);

    bool cmp_badd_num(int& address, int& num);

    bool je(string& label);

    bool jne(string& label);

    bool ja(string& label);

    bool jae(string& label);

    bool jb(string& label);

    bool jbe(string& label);

    bool inc_reg16(unsigned short& reg);

    bool inc_reg8(unsigned char& reg);

    bool inc_wadd(int& address);

    bool inc_badd(int& address);

    bool dec_reg16(unsigned short& reg);

    bool dec_reg8(unsigned char& reg);

    bool dec_wadd(int& address);

    bool dec_badd(int& address);

    bool int21h();
}

#endif /* instruction_hpp */