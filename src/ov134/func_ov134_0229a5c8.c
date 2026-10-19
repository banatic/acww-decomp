/* func_ov134_0229a5c8 @ 0x0229a5c8, 0x23c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[4];
    int unk_04;
    u8 unk_08[0x10];
    char pad_18[0x74 - 0x18];
    void *unk_74;
    void *unk_78;
    int unk_7C;
    char pad_80[0x8c - 0x80];
    int unk_8C;
    char pad_90[0xa4 - 0x90];
    u8 a4;
    u8 a5;
    char pad_A6[1];
    u8 a7;
    u8 a8;
    u8 a9;
    u8 aa;
    u8 ab;
    u8 ac;
    char pad_AD[1];
    u8 ae;
    u8 af;
    u8 b0;
    char pad_B1[0xb5 - 0xb1];
    u8 b5;
    u8 b6;
    char pad_B7[0xbc - 0xb7];
    u8 bc;
    u8 bd;
    char pad_BE[0x1070 - 0xbe];
    char unk_1070[0x1870 - 0x1070];
    u16 unk_1870[0x20 * 0x20];
} UnkStruct_0229a5c8;

extern void func_0200467c(int);
extern void func_0200277c(int);
extern u8 func_ov134_0229aaa8(UnkStruct_0229a5c8 *, int);
extern u8 func_ov134_0229aa78(UnkStruct_0229a5c8 *, int);
extern void MIi_CpuCopy16(void *, void *, int);
extern int func_ov134_0229aa6c(UnkStruct_0229a5c8 *, int);
extern u8 func_0209de24(int, int);
extern u8 func_ov134_0229b884(UnkStruct_0229a5c8 *, int);
extern void func_ov134_0229a1d8(UnkStruct_0229a5c8 *, int);
extern void func_ov134_02299a3c(UnkStruct_0229a5c8 *);
extern void func_ov134_0229a918(UnkStruct_0229a5c8 *, int, int);
extern void func_ov134_0229a868(UnkStruct_0229a5c8 *, u8);
extern int func_ov134_0229aa3c(UnkStruct_0229a5c8 *, int);
extern void func_ov134_0229b5f4(UnkStruct_0229a5c8 *, int, int, int, int, int);
extern void func_ov134_022995b0(UnkStruct_0229a5c8 *, int);
extern void func_02001b6c(int);
extern void func_02001d74(int, int);
extern int func_02002d8c(int);
extern void func_02001d00(int);
extern void func_ov134_022995d4(UnkStruct_0229a5c8 *, int);

extern u8 data_ov134_0229bf64[];
extern u8 data_ov134_0229bf5c[];
extern char data_ov134_0229c294;
extern char data_ov134_0229c164;
extern char data_ov134_0229c2c4;
extern char data_ov134_0229c11c;

void func_ov134_0229a5c8(UnkStruct_0229a5c8 *p, int mode)
{
    int n;
    int w;
    int i;
    int j;
    int k;
    u8 v;
    int t;
    u16 *row;

    func_0200467c(0x13);
    p->a5 = (u8) mode;
    p->a9 = 0;
    func_0200277c(p->a4);
    p->a7 = func_ov134_0229aaa8(p, mode);
    p->a8 = func_ov134_0229aa78(p, mode);
    MIi_CpuCopy16(p->unk_1070, p->unk_1870, 0x800);
    n = func_ov134_0229aa6c(p, mode);
    w = 8 - n;
    row = p->unk_1870;
    for (i = 0; i < 0x20; i++) {
        for (j = 0; j < w; j++) {
            row[j] = 0x10;
        }
        row[(w - 1) & 0x1f] = 0x3079;
        row = row + 0x20;
    }
    p->aa = (u8) ((p->a7 - w) << 3);
    p->ab = 0x28;
    p->ac = data_ov134_0229bf64[mode];
    if (mode == 2) {
        p->ac = func_0209de24(p->bd, p->bc);
    }
    p->unk_8C = (p->ac - 8) << 4;
    for (k = 0; k < 0x10; k++) {
        p->unk_08[k] = 0xff;
    }
    v = func_ov134_0229b884(p, p->a5);
    if (p->a5 == 1 || p->a5 == 2) {
        v = (u8) (v - 1);
    }
    t = (v << 4) - ((p->a8 << 3) - p->ab);
    if (t < 0) {
        t = 0;
    } else if (t > p->unk_8C) {
        t = p->unk_8C;
    }
    func_ov134_0229a1d8(p, t);
    func_ov134_02299a3c(p);
    func_ov134_0229a918(p, mode, 0xa);
    func_ov134_0229a868(p, (u8) mode);
    p->unk_7C = func_ov134_0229aaa8(p, p->a5) << 3;
    p->ae = (u8) (func_ov134_0229aa3c(p, mode) << 3);
    p->b5 = (u8) (p->ae - 8);
    p->b6 = (u8) (p->ae + 8);
    func_ov134_0229b5f4(p, 8, 0x1aa, 8, data_ov134_0229bf5c[mode], n + 1);
    func_ov134_022995b0(p, 0x200);
    if (mode == 0) {
        p->unk_74 = &data_ov134_0229c294;
        p->unk_78 = &data_ov134_0229c164;
    } else {
        p->unk_74 = &data_ov134_0229c2c4;
        p->unk_78 = &data_ov134_0229c11c;
    }
    p->af = 3;
    func_02001b6c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~func_02002d8c(p->a4) & 0x1f);
    func_ov134_022995d4(p, 0);
    p->b0 = (u8) (v + 1);
    p->unk_04 = 0;
}
