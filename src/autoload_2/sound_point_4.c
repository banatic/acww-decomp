/* sound_point_4: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f52a0 @ 0x020f52a0, 0xc0 bytes, ARM
 * func_020f51c4 @ 0x020f51c4, 0xdc bytes, ARM
 * func_020f5178 @ 0x020f5178, 0x4c bytes, ARM
 */

#include "types.h"

struct UnkStruct_020f52a0 {
    int pad_00;
    int pad_04;
    int pad_08;
    int a;
    int b;
    int c;
    unsigned short v;
    unsigned char flag1;
    unsigned char flag2;
};

typedef struct UnkStruct_020f51c4 {
    char pad_00[0x3a];
    u16 unk_3A;
} UnkStruct_020f51c4;

typedef struct UnkStruct_020f51c4_2 {
    char pad_00[8];
    UnkStruct_020f51c4 *unk_08;
    char pad_0C[0x18 - 0xc];
    u16 unk_18;
} UnkStruct_020f51c4_2;

extern unsigned char data_021fd1bc[];
extern void *data_021fd234;
extern void func_020f4eec(void *ptr, void *out);
extern void func_020f4c70(void *ptr, unsigned short val, int *data);
extern void func_020f50e4(void *out);
extern int func_020eed18(void *p, int k);
extern int func_020eedb8(u16 m, int k, void *p);

void func_020f5178(void *p);

void func_020f52a0(struct UnkStruct_020f52a0 *out, int value, int *src)
{
    if (data_021fd1bc[0x4d] != 0) {
        return;
    }
    out->a = src[0];
    out->b = src[1];
    out->c = src[2];
    if (value > 0x3e9 && value < 0x430) {
        out->v = value;
        out->flag1 = 1;
        out->flag2 = 1;
        func_020f4eec(data_021fd234, out);
        return;
    } else {
        func_020f5178(out);
        func_020f4c70(data_021fd234, (unsigned short) value, &out->a);
        func_020f50e4(out);
        return;
    }
}

void func_020f51c4(UnkStruct_020f51c4_2 *s)
{
    unsigned int ok;
    int a;
    int b;
    UnkStruct_020f51c4 *p;

    p = s->unk_08;
    a = 0;
    ok = (p != 0);
    if (ok) {
        if (p->unk_3A != s->unk_18 % 1000) {
            b = 1;
            a = b;
        } else {
            b = 0;
            a = b;
        }
    } else {
        b = 1;
    }
    if (a) {
        func_020eed18(&s->unk_08, 5);
    }
    if (b) {
        func_020eedb8((u16) (s->unk_18 % 1000), 1, &s->unk_08);
    }
    func_020f50e4((void *) s);
}

void func_020f5178(void *p)
{
    if (data_021fd1bc[0x4d] != 0) {
        func_020eed18((char *) p + 8, 0xf);
    } else {
        func_020eed18((char *) p + 8, 0);
    }
}
