/* field_actor_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200e704 @ 0x0200e704, 0xf4 bytes, Thumb
 * func_0200e6a4 @ 0x0200e6a4, 0x60 bytes, Thumb
 * func_0200e654 @ 0x0200e654, 0x50 bytes, Thumb
 * func_0200e42c @ 0x0200e42c, 0x228 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0200e6a4 UnkStruct_0200e6a4;

struct UnkStruct_0200e6a4 {
    char pad_00[0x428];
    char pad_428[0x3D8];
    unsigned int value;
};

struct UnkStruct_0200e654 {
    char pad_00[0x59c];
    char unk_59C;
    char pad_59D[0x800 - 0x59c - 1];
    int unk_800;
};

typedef struct UnkStruct_0200e42c {
    int x;
    int y;
    int z;
} UnkStruct_0200e42c;

typedef struct UnkStruct_0200e42c_2 {
    int a;
    int b;
} UnkStruct_0200e42c_2;

typedef struct UnkStruct_0200e42c_3 {
    char pad_00[8];
    int unk_08;
    char pad_0C[80];
    UnkStruct_0200e42c unk_5C;
    char pad_68[52];
    unsigned int unk_9C;
    unsigned int unk_A0;
    char pad_A4[196];
    int unk_168;
    char unk_16C;
    char pad_16D[1075];
    char unk_5A0;
    char pad_5A1[39];
    char unk_5C8;
    char pad_5C9[291];
    int unk_6EC;
    char pad_6F0[4];
    int unk_6F4;
    int unk_6F8;
    int unk_6FC;
    char pad_700[13];
    char unk_70D;
    char unk_70E;
    char unk_70F;
    char pad_710[144];
    char unk_7A0;
    char pad_7A1[95];
    int unk_800;
    int unk_804;
    int unk_808;
    int unk_80C;
    int unk_810;
    int unk_814;
    int unk_818;
    int unk_81C;
    char pad_820[200];
    char unk_8E8;
    char unk_8E9;
    char pad_8EA[26];
    unsigned char unk_904;
} UnkStruct_0200e42c_3;

extern void func_0205d0b8(void *, u8);
extern int func_02011340(void *);
extern void func_0205d058(void *, int);
extern void func_0205d4f0(void *, u8);
extern void func_0201131c(void *, void *);
extern void func_02010680(void *, void *);
extern int func_0205cfd4(void *);
extern int func_0205d25c(void *);
extern int func_0205f8b4(void *);
extern void func_0205d034(void *);
extern void func_020100d0(void *, int, int, void *, void *);
extern void func_020100b8(void *, int, int, void *, void *);
extern int func_021077e8(int);
extern const u8 data_020c75d8[];
extern const u8 data_020c75d0[];
extern int data_020d83e8;
extern int data_020d83f0;
extern unsigned char data_020c75e4[];
extern void func_0205e4e8(void *, unsigned char);
extern void func_020112f8(unsigned short *, UnkStruct_0200e6a4 *);
extern int func_020112e4(UnkStruct_0200e6a4 *);
extern int func_020112d0(UnkStruct_0200e6a4 *);
extern int func_020100e8(UnkStruct_0200e6a4 *, unsigned short *, int, int, int);
extern int func_020961d0(int);
extern void func_0205df14(char *ptr, unsigned char val);
extern void func_02011138(void *dst, void *src);
extern int func_020103c0(void *a, void *b);
extern void func_02010424(void *a);
extern unsigned char data_020c75c8[];
extern int func_02096188(int);
extern void func_0203efb0(UnkStruct_0200e42c_3 *, unsigned short);
extern void func_020962c8(int, UnkStruct_0200e42c_3 *);
extern void func_0205f8cc(void *, int);
extern int func_02011150(UnkStruct_0200e42c_3 *, int);
extern void func_020106a8(UnkStruct_0200e42c_3 *, int, int);
extern void func_0205db4c(void *, int);
extern void func_0205d8c4(void *, int);
extern void func_0205dccc(void *, int);
extern int func_020110e8(UnkStruct_0200e42c_3 *);
extern int func_0205dc94(void *, int);
extern void func_020110c4(UnkStruct_0200e42c_2 *, UnkStruct_0200e42c_3 *);
extern int func_02011368(UnkStruct_0200e42c_3 *);
extern void func_0205ec50(void *, int, UnkStruct_0200e42c_3 *, UnkStruct_0200e42c_2 *, int, int);
extern void func_02060500(void *, int);
extern int func_02096180(int);
extern int func_0200dbb4(UnkStruct_0200e42c_3 *, int, int, int);
extern void func_02006554(UnkStruct_0200e42c_3 *);
extern unsigned int *func_0200f27c(UnkStruct_0200e42c_3 *, int);
extern unsigned char data_020c75c4[];
extern unsigned char data_020c75d4[];
extern unsigned char data_020c75dc[];
extern unsigned char data_020c75cc[];
extern unsigned char data_020c75e0[];
extern unsigned char data_020e54a8;

void func_0200e704(unsigned char *self)
{
    struct {
        int x;
    } local;
    int a, b, c;

    func_0205d0b8(self + 0x389, data_020c75d8[func_020961d0(*(u32 *) (self + 0x800))]);

    if (func_02011340(self) == 0) {
        func_0205d058(self + 0x389, 0);
    } else {
        func_0205d058(self + 0x389, 1);
    }

    func_0205d4f0(self + 0x774, data_020c75d0[func_020961d0(*(u32 *) (self + 0x800))]);

    func_0201131c(&local, self);
    func_02010680(self, &local);

    a = func_021077e8(func_0205cfd4(self + 0x389));
    b = func_021077e8(func_0205d25c(self + 0x774));
    func_020100d0(self, b, a, &data_020d83e8, &data_020d83e8);
    func_020100b8(self, b, a, &data_020d83e8, &data_020d83e8);

    c = func_021077e8(func_0205f8b4(self + 0x7a0));
    func_020100b8(self, c, func_021077e8(func_0205cfd4(self + 0x389)), &data_020d83f0, &data_020d83f0);
    func_0205d034(self + 0x389);
}

void func_0200e6a4(UnkStruct_0200e6a4 *obj)
{
    unsigned short s1;
    unsigned short s2;
    int idx;
    idx = func_020961d0(obj->value);
    func_0205e4e8((char *) obj + 0x428, data_020c75e4[idx]);
    func_020112f8(&s2, obj);
    s1 = s2;
    func_020100e8(obj, &s1, func_020112e4(obj), func_020112d0(obj), 1);
}

void func_0200e654(struct UnkStruct_0200e654 *s)
{
    unsigned short local[4];
    int idx;
    idx = func_020961d0(s->unk_800);
    func_0205df14(&s->unk_59C, data_020c75c8[idx]);
    func_02011138(local, s);
    local[1] = local[0];
    func_020103c0(s, &local[1]);
    func_02010424(s);
}

int func_0200e42c(UnkStruct_0200e42c_3 *s)
{
    int h;
    int idx;
    int t;
    UnkStruct_0200e42c *v;
    UnkStruct_0200e42c_2 loc;

    h = s->unk_08;
    s->unk_800 = func_02096188(h);
    func_0203efb0(s, (unsigned short) s->unk_800);
    func_020962c8(s->unk_800, s);
    func_0205f8cc(&s->unk_7A0, data_020c75c4[func_020961d0(s->unk_800)]);
    idx = func_020112d0((UnkStruct_0200e6a4 *) s);
    func_020106a8(s, idx, func_02011150(s, 1));
    func_0200e704((unsigned char *) s);
    func_0205db4c(&s->unk_70F, data_020c75d4[func_020961d0(s->unk_800)]);
    func_0205d8c4(&s->unk_70E, data_020c75dc[func_020961d0(s->unk_800)]);
    func_0205dccc(&s->unk_70D, data_020c75cc[func_020961d0(s->unk_800)]);
    func_0205dc94(&s->unk_70D, func_020110e8(s));
    func_0200e6a4((UnkStruct_0200e6a4 *) s);
    func_0200e654((struct UnkStruct_0200e654 *) s);
    idx = func_020961d0(s->unk_800);
    func_020110c4(&loc, s);
    func_0205ec50(&s->unk_5A0, data_020c75e0[idx], s, &loc, func_02011368(s), 0);
    func_02060500(&s->unk_5C8, s->unk_800);
    s->unk_9C = 0xffffb000;
    s->unk_A0 = 0xffff6000;
    func_0200dbb4(s, func_02096180(h), 9, -1);
    s->unk_904 &= ~0x80;
    func_02006554(s);
    s->unk_6EC = 0;
    func_0200f27c(s, 1);
    t = data_020e54a8 ? 0 : 1;
    if (t != 0) {
        func_0200f27c(s, 0);
    }
    v = &s->unk_5C;
    s->unk_6F4 = v->x;
    s->unk_6F8 = v->y;
    s->unk_6FC = v->z;
    s->unk_80C = -1;
    s->unk_810 = -1;
    s->unk_804 = -1;
    s->unk_808 = 0;
    s->unk_814 = 0;
    s->unk_818 = 0;
    s->unk_81C = 0xf;
    s->unk_8E9 = 0x1f;
    s->unk_8E8 = 0;
    s->unk_168 = 0;
    s->unk_16C = 0;
    return 1;
}
