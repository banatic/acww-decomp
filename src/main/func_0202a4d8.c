/* func_0202a4d8 @ 0x0202a4d8, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0202a4d8 {
    u16 unk_00;
    u8 nm[12];
    u8 unk_0E;
    u8 unk_0F;
} UnkStruct_0202a4d8;
typedef struct UnkStruct_0202a4d8_2 {
    s32 w[8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
} UnkStruct_0202a4d8_2;
typedef struct UnkStruct_0202a4d8_3 {
    s32 a, b;
} UnkStruct_0202a4d8_3;

typedef struct UnkStruct_0202a4d8_4 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x11c];
    void *unk_160;
} UnkStruct_0202a4d8_4;

extern UnkStruct_0202a4d8_3 data_020d8f48;
extern u8 data_020c8928[];
extern u8 data_020c8924[];
extern u8 data_021c2ee4[];
extern u8 data_021c1e14[];
extern u8 data_021c1d6c[];

extern void *func_0209ad9c(int, int);
extern void *func_0209b4d4(void *);
extern int func_0209bd44(void *);
extern int func_0209bba8(void *);
extern UnkStruct_0202a4d8 *func_0209b4cc(void *, int);
extern UnkStruct_0202a4d8 *func_0208150c(UnkStruct_0202a4d8 *);
extern int memcmp(const void *, const void *, int);
extern int func_0209b414(void *);
extern int func_0209bc40(void *);
extern void func_0201cfb4(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *);
extern void func_0202d9d0(UnkStruct_0202a4d8_4 *, void *);
extern void func_0201cf90(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *, int, int, int, void *);
extern void func_0201cf74(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *, int, void *, void *);
extern void func_0201cec8(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_2 *);
extern void func_0202da74(UnkStruct_0202a4d8_4 *, UnkStruct_0202a4d8_3);
extern void func_02068388(void *, int);

int func_0202a4d8(UnkStruct_0202a4d8_4 *p, UnkStruct_0202a4d8 *b, int c)
{
    void *h;
    void *t;
    int ret;
    UnkStruct_0202a4d8 *x;
    UnkStruct_0202a4d8_2 s;

    h = func_0209ad9c(c, 0);
    t = func_0209b4d4(h);
    ret = 0;
    if (func_0209bd44(t)) {
        if (func_0209bba8(t) == 1) {
            x = func_0209b4cc(h, 1);
            b = func_0208150c(b);
            if (b->unk_00 == x->unk_00 && memcmp(b->nm, x->nm, 12) == 0 && b->unk_0F == x->unk_0F && func_0209b414(h) == 0) {
                switch (func_0209bc40(t)) {
                    case 0xe:
                    case 0x10:
                    case 0x11:
                        func_0201cfb4(p, &s);
                        p->unk_160 = h;
                        func_0202d9d0(p, t);
                        func_0201cf90(p, &s, 0, 0x1d, 0x1d, data_021c2ee4);
                        func_0201cf74(p, &s, 1, data_020c8928, data_021c1e14);
                        func_0201cf74(p, &s, 2, data_020c8924, data_021c1d6c);
                        s.unk_20 = 3;
                        s.unk_21 = s.unk_20 - 1;
                        func_0201cec8(p, &s);
                        func_0202da74(p, data_020d8f48);
                        func_02068388(p->unk_40, 1);
                        ret = 1;
                        break;
                }
            }
        }
    }
    return ret;
}
