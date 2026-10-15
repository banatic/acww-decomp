/* func_ov096_0229cf84 @ 0x0229cf84, 0x160 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x294c];
    char unk_294C;
} UnkStruct_0229cf84;

extern int func_0206fe54(void);
extern int func_ov002_02208d4c(void *p, int a, int b);
extern int func_ov096_0229f088(UnkStruct_0229cf84 *self, int a);
extern unsigned short func_ov096_0229f0dc(UnkStruct_0229cf84 *self, int a);
extern int func_0208b500(void);
extern int func_0208d12c(void *argument0);
extern int func_ov096_0229daec(UnkStruct_0229cf84 *self, int a);
extern void func_ov098_022a30a4(UnkStruct_0229cf84 *self, int a);
extern int func_020b67d4(void);
extern void func_ov097_022a28e4(UnkStruct_0229cf84 *self, int a);
extern int func_ov094_02299a90(int a);
extern u8 data_020e54a8;

void func_ov096_0229cf84(UnkStruct_0229cf84 *self, int arg)
{
    volatile u16 t;
    int k;
    int id;

    if (func_0206fe54() != 0) {
        func_ov002_02208d4c(&self->unk_294C, 0, 0);
    }
    k = func_ov096_0229f088(self, arg);
    id = func_ov096_0229f0dc(self, arg);
    t = (u16) id;
    if (k == 0) {
        unsigned int ok = 0;
        u16 lo = t;
        u16 hi = t;
        if (hi >= 0x156c && lo <= 0x156c) {
            ok = 1;
        }
        if (ok != 0) {

            if (func_0208d12c((void *) func_0208b500()) != 0) {
                func_ov002_02208d4c(&self->unk_294C, 0xdc, 0x1b);
            } else {
                func_ov002_02208d4c(&self->unk_294C, 0xe1, 0x1c);
            }
        }
    }
    switch (k) {
        case 0: {
            unsigned int ok;
            int q;
            u16 lo, hi;
            if (func_ov096_0229daec(self, id) != 0) {
                ok = (data_020e54a8 == 0) ? 1 : 0;
                if (ok != 0) {
                    q = 1;
                } else {
                    q = 0xa;
                }
                func_ov002_02208d4c(&self->unk_294C, q, 2);
            }
            ok = (data_020e54a8 == 0) ? 1 : 0;
            if (ok != 0) {
                func_ov098_022a30a4(self, id);
            } else if (func_020b67d4() != 0) {
                func_ov097_022a28e4(self, id);
            }
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1000 && lo <= 0x10ff) {
                ok = 1;
            }
            if (ok != 0) {
                func_ov002_02208d4c(&self->unk_294C, 0x1c, 7);
            } else if (lo >= 0x151f && lo <= 0x151f) {
                func_ov002_02208d4c(&self->unk_294C, 0x1c, 8);
            }
        } break;
        case 1:
            func_ov002_02208d4c(&self->unk_294C, 9, 0x14);
            break;
        case 2:
            if (func_ov094_02299a90(id) == 0) {
                func_ov002_02208d4c(&self->unk_294C, 0x17, 0x14);
            }
            break;
    }
}
