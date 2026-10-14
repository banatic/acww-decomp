/* func_ov068_02274b44 @ 0x02274b44, 0x284 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x8e - 0x68];
    u16 unk_8E;
    char pad_90[4];
    u16 unk_94;
    char pad_96[0x2a0 - 0x96];
    char unk_2A0[0x3b0 - 0x2a0];
    char unk_3B0[0x511 - 0x3b0];
    u8 unk_511;
    char pad_512[0x65c - 0x512];
    char unk_65C[0x730 - 0x65c];
    int unk_730;
} UnkStruct_02274b44;

typedef struct {
    int lo;
    int hi;
} TM;

extern void *data_020ccf94;
extern u8 data_021f3b85;
extern u8 data_021ebcd3;
extern u8 data_021f395c;
extern u16 data_ov068_022767ec[];
extern char data_021fbee8[];
extern int data_020c814c;

extern int func_0202edc8(void);
extern void func_0201c280(UnkStruct_02274b44 *self, char *p);
extern void func_ov068_022746c0(char *p, UnkStruct_02274b44 *self);
extern void func_0209e474(TM *t);
extern int func_02073dd4(void *g, void *h);
extern int func_0209fa30(u8 *p);
extern int func_0209ded0(void);
extern void func_02003348(int a, int b, int c, int d, int e);
extern int func_02086eb0(u8 *p);
extern int func_020af028(u8 *p);
extern unsigned int func_02086ecc(u8 *p);
extern unsigned int func_02086ec4(u8 *p);
extern int func_02086ed4(u8 *p);
extern void func_0201c400(UnkStruct_02274b44 *self, u16 *p);
extern void func_0203edf4(UnkStruct_02274b44 *self, int a);
extern void func_0201b38c(char *p, int a);
extern void func_0201b388(char *p, int a);
extern void func_0201b384(char *p, int a);
extern void func_0201ad18(char *p, int a, int b, int c, char *d, int e, int f, int g);
extern void func_0201ad88(char *p, int a);

int func_ov068_02274b44(UnkStruct_02274b44 *self)
{
    u16 cmd;
    TM tm;
    u8 *pp;
    u8 hh;
    u8 mm;
    int mode;
    unsigned int t;

    if (func_0202edc8() == 0) {
        return 0;
    }
    func_0201c280(self, self->unk_65C);
    func_ov068_022746c0(self->unk_65C, self);
    self->unk_511 = 0;
    tm.lo = 0;
    tm.hi = 0;
    func_0209e474(&tm);
    hh = ((u8 *) &tm)[2];
    mm = ((u8 *) &tm)[1];
    self->unk_730 = 8;
    if (func_02073dd4(data_020ccf94, ((void **) data_020ccf94)[0x19]) != 0) {
        return 1;
    }
    if (func_0209fa30(&data_021f3b85) != 0) {
        return 1;
    }
    pp = &data_021ebcd3;
    mode = func_0209ded0();
    switch (mode) {
        case 6:
            if ((hh == 0x13 && mm >= 0x1e) || hh == 0x14 || hh == 0x15 || hh == 0x16 || (hh == 0x17 && mm <= 0x3b)) {
                self->unk_730 = 7;
                func_02003348(0x10, 0, 0, 0, 0);
            }
            break;
        case 0:
            if (hh == 0x15 && mm < 0x37) {
                self->unk_730 = 1;
            }
            break;
        default:
            if (hh == 0x15 && mm < 0x37) {
                self->unk_730 = 1;
            }
            if (hh == 0x17 && mm <= 0x3b) {
                if (func_02086eb0(pp) != 0) {
                    if (func_020af028(&data_021f395c) == 3) {
                        self->unk_730 = 2;
                    }
                }
            }
            break;
    }
    if (hh == 0xc || (hh == 0xd && mm < 0x1e)) {
        t = func_02086ecc(pp);
        switch (t) {
            case 2:
                self->unk_730 = 5;
                break;
            case 1:
                self->unk_730 = 4;
                break;
            case 3:
                self->unk_730 = 6;
                break;
            case 4:
                self->unk_730 = 3;
                break;
        }
    }
    if ((hh == 0xe && mm >= 0x1e) || (hh == 0xf && mm <= 0x3b)) {
        t = func_02086ec4(pp);
        switch (t) {
            case 2:
                self->unk_730 = 5;
                break;
            case 1:
                self->unk_730 = 4;
                break;
            case 3:
                self->unk_730 = 6;
                break;
            case 4:
                self->unk_730 = 3;
                break;
        }
    }
    if (hh == 6 && mm < 0x37) {
        if (func_02086ed4(pp) != 0) {
            self->unk_730 = 0;
        }
    }
    cmd = data_ov068_022767ec[self->unk_730];
    func_0201c400(self, &cmd);
    if (self->unk_730 == 7) {
        func_0203edf4(self, 0x5000);
        self->unk_5C = 0xf000;
        self->unk_64 = 0x13000;
        self->unk_8E = 0;
        self->unk_94 = 0;
        func_0201b38c(self->unk_2A0, 0x102);
        func_0201b388(self->unk_2A0, 0x102);
        func_0201b384(self->unk_2A0, 0x102);
        func_0201ad18(self->unk_3B0, 0, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    } else {
        func_0201b38c(self->unk_2A0, 0x1e);
        func_0201b388(self->unk_2A0, 0x1e);
        func_0201b384(self->unk_2A0, 0x1e);
        func_0201ad88(self->unk_3B0, 0);
    }
    return 1;
}
