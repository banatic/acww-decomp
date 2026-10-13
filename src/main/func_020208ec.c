/* func_020208ec @ 0x020208ec, 0x170 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020208ec_3 {
    void *ptr;
    u8 byte;
} UnkStruct_020208ec_3;

typedef void (*Fn)(void *self2, UnkStruct_020208ec_3 *out);

typedef struct Pmf {
    int idx;
    int adj;
} Pmf;

typedef struct UnkStruct_020208ec {
    void *unk_00;
    u8 unk_04;
    u8 pad_05[0x82b];
    void *unk_830;
} UnkStruct_020208ec;

typedef struct UnkStruct_020208ec_4 {
    u8 pad_00[0xb0];
    Pmf pmf;
    u8 pad_B8[0x100 - 0xb8];
    UnkStruct_020208ec *unk_100;
    char arr_104[0x1e];
    u8 unk_122;
    u8 pad_123[5];
    u32 unk_128;
    u32 unk_12C;
} UnkStruct_020208ec_4;

typedef struct UnkStruct_020208ec_2 {
    u32 a;
    u8 b;
} UnkStruct_020208ec_2;

extern UnkStruct_020208ec_2 data_020c8ab0;
extern char data_021e5a2c;
extern char data_021c2454;
extern char data_021c24fc;
extern char data_021c2514;

extern int func_02020a5c(UnkStruct_020208ec_4 *self, UnkStruct_020208ec_3 *out);
extern void func_0202d8f8(void *self, void *p12c, void *p128, void *p830, int zero);
extern int func_020819bc(void *a);
extern void *func_0208150c(void *a);
extern int func_020036e8(void *a);
extern void func_0202da38(void *self, void *p104, void *p122, int len, int e, u32 a, int b, int h, int i);
extern int func_0207a47c(void *a, void *b);
extern int func_020644cc(int a);
extern void func_0202da88(UnkStruct_020208ec_4 *self, void *str);
extern void func_020819e0(void *a);

void func_020208ec(UnkStruct_020208ec_4 *self, UnkStruct_020208ec_3 *out)
{
    void *f830;

    f830 = self->unk_100->unk_830;
    if (func_02020a5c(self, out) != 0) {
        func_0202d8f8(self, (void *) &self->unk_12C, (void *) &self->unk_128, self->unk_100->unk_830, 0);
    } else {
        func_0202d8f8(self, (void *) &self->unk_12C, (void *) &self->unk_128, self->unk_100->unk_830, 0);
        if (self->unk_12C != 0 && func_020819bc((void *) self->unk_12C) == 0) {
            func_0202da38(self, self->arr_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(f830)), data_020c8ab0.a,
                          data_020c8ab0.b, 0, 0);
            out->ptr = self->arr_104;
            out->byte = self->unk_122;
            func_020819e0((void *) self->unk_12C);
        } else {
            if (func_0207a47c((void *) &data_021e5a2c, func_0208150c(f830)) == 0) {
                switch (func_020644cc(3)) {
                    case 0:
                        func_0202da88(self, &data_021c2454);
                        break;
                    case 1:
                        func_0202da88(self, &data_021c24fc);
                        break;
                    default:
                        func_0202da88(self, &data_021c2514);
                        break;
                }
                if (((volatile Pmf *) &self->pmf)->idx != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn f;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        f = (Fn) * (int *) (*(char **) t + pm->idx);
                    } else {
                        f = (Fn) pm->idx;
                    }
                    f(t, out);
                }
            } else {
                func_0202da88(self, &data_021c2514);
                if (((volatile Pmf *) &self->pmf)->idx != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn f;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        f = (Fn) * (int *) (*(char **) t + pm->idx);
                    } else {
                        f = (Fn) pm->idx;
                    }
                    f(t, out);
                }
            }
        }
    }
}
