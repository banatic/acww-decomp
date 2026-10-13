/* func_0202551c @ 0x0202551c, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u32 lo;
    u32 hi;
};

struct Arg {
    u32 word;
    u8 byte;
    u8 pad[3];
};

struct UnkStruct_0202551c {
    u8 unk_00;
    u8 pad1;
    u16 unk_02;
    struct Arg arg;
};

struct Field40 {
    u32 pad[2];
    u32 unk_08;
};

class UnkStruct_0202551c_2;
typedef void (UnkStruct_0202551c_2::*PMF)(struct Arg *);

class UnkStruct_0202551c_2 {
  public:
    char pad_00[0x40];
    struct Field40 *unk_40;
    char pad1[0xb0 - 0x44];
    PMF pmf;
    char pad_B8[0x124 - 0xb8];
    u16 unk_124;
};

extern "C" int func_0206fc6c(UnkStruct_0202551c_2 *self);
extern "C" void *func_0206fc8c(int param);
extern "C" void *func_020984e8(void *p);
extern "C" void *func_02099734(void *p);
extern "C" u16 *func_02098f48(void *a, void *b);
extern "C" void func_0209a088(void *p, int n, void *r);
extern "C" void func_02015330(UnkStruct_0202551c_2 *self, void *p, int a, int b, int c);
extern "C" void func_0202dbdc(UnkStruct_0202551c_2 *self, struct Pair v);
extern "C" void func_0202da88(UnkStruct_0202551c_2 *self, int *g);
extern "C" void func_0206844c(void *ptr, u8 *byteptr, u32 word);

extern int data_021c2adc;
extern struct Pair data_020d91c0;

extern "C" void func_0202551c(UnkStruct_0202551c_2 *self)
{
    UnkStruct_0202551c local;
    int cond = func_0206fc6c(self);
    if (cond == 0) {
        if (self->unk_40 != 0) {
            self->unk_40->unk_08 = 1;
        }
        func_0202da88(self, &data_021c2adc);
        if (self->pmf) {
            (self->*self->pmf)(&local.arg);
        }
        local.unk_00 = local.arg.byte;
        func_0206844c(self->unk_40, &local.unk_00, local.arg.word);
    } else {
        void *r = func_0206fc8c(cond);
        void *a = func_020984e8(r);
        void *b = func_02099734(a);
        u16 *res = func_02098f48(b, r);
        self->unk_124 = *res;
        local.unk_02 = 0xFFF1;
        func_0209a088(&local.unk_02, 0, r);
        func_02015330(self, &self->unk_124, 0, 4, 0);
        func_0202dbdc(self, data_020d91c0);
    }
}
