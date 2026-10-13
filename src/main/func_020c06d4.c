/* func_020c06d4 @ 0x020c06d4, 0x1e4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020c06d4 UnkStruct_020c06d4;
struct UnkStruct_020c06d4 {
    u8 pad_00[0x4];
    int unk_04;
    int unk_08;
    int unk_0C;
    u8 pad_10[0x14];
    int unk_24;
    u8 pad_28[0x6];
    u8 unk_2E;
    u8 pad_2F[0x5];
    int unk_34;
    int unk_38;
    u8 pad_3C[0x4];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    u8 pad_50[0x10];
    int unk_60;
    int unk_64;
    int unk_68;
};

typedef struct Elem12 {
    int a;
    int b;
    int c;
} Elem12;

extern Elem12 data_021fa678[];
extern int data_021fbaf0;
extern int data_021fbee8[3];

extern int func_020bf514(UnkStruct_020c06d4 *, int, int, int);
extern int func_020bf308(UnkStruct_020c06d4 *, int, int, int);
extern void func_020bee60(void *, int);
extern void func_020bf26c(UnkStruct_020c06d4 *, int);
extern void func_020beb48(int *);
extern void func_020bf248(UnkStruct_020c06d4 *, int);
extern void func_020bf5b8(UnkStruct_020c06d4 *, int);
extern int func_0208a160(void *, int);
extern void func_02040ba0(int);
extern void func_020952ec(void);
extern int func_02095794(void);
extern void func_020b2b8c(int, int);
extern void func_020beb3c(int *);
extern void func_020beb00(int *, int, int, int, int);
extern void VEC_Add(void *, void *, void *);
extern void func_020eabc8(void *, int);
extern void func_020c08fc(UnkStruct_020c06d4 *);

void func_020c06d4(UnkStruct_020c06d4 *s)
{
    int state;
    int temp[3];
    int v;
    int ret;

    state = s->unk_60;

    if (state == 0) {
        if (func_020bf514(s, 0x385, 0x1000, 0xfa0) != 0) {
            s->unk_04 = 3;
        } else {
            if (func_020bf308(s, 0x1a000, 0xc000, 0x5000) != 0) {
                func_020bee60(&data_021fa678[s->unk_24], 0x24);
                s->unk_08 = 0x24;
                func_020bf26c(s, 0x7fc);
                func_020beb48(&data_021fbaf0);
                s->unk_60 = 1;
            } else {
                func_020bf248(s, 0x7fb);
            }
        }
    } else if (state == 1) {
        s->unk_0C = 0x17;
        func_020bf5b8(s, 0x17);
        s->unk_40 = (s->unk_2E != 0) ? 0x2666 : -0x2666;
        s->unk_44 = -0x399A;
        s->unk_48 = 0;
        s->unk_60 = 2;
    } else if (state == 2) {
        if (func_0208a160((char *) s + 0x10, state) != 0) {
            func_020bee60(&data_021fa678[s->unk_24], 0x25);
            s->unk_08 = 0x25;
            s->unk_60 = 3;
            s->unk_64 = 1;
        }
    } else if (state == 3) {
        s->unk_0C = 0x18;
        func_020bf5b8(s, 0x18);
        s->unk_60 = 4;
        s->unk_68 = 0;
    } else if (state == 4) {
        if (s->unk_38 > 0xd0000) {
            func_02040ba0(0x44);
            func_020952ec();
            ret = func_02095794();
            func_020b2b8c(ret, (s->unk_2E == 0) ? 1 : 0);
            func_020beb3c(&data_021fbaf0);
            s->unk_04 = 3;
        }
    }

    if (s->unk_60 >= 2) {
        temp[0] = data_021fbee8[0];
        temp[1] = data_021fbee8[1];
        temp[2] = data_021fbee8[2];

        if (s->unk_60 >= 4) {
            temp[0] = (s->unk_2E != 0) ? 0x19a : -0x19a;
            temp[1] = 0x19a;
            v = 0xfd7;
        } else {
            temp[1] = 0x800;
            v = 0x1000;
        }

        VEC_Add(&s->unk_40, temp, &s->unk_40);
        func_020eabc8(&s->unk_40, v);
        VEC_Add(&s->unk_34, &s->unk_40, &s->unk_34);
    }

    if (s->unk_60 >= 1) {
        func_020beb00(&data_021fbaf0, s->unk_34, s->unk_38, s->unk_4C, (s->unk_2E == 0) ? 1 : 0);
    }

    func_020c08fc(s);
}
