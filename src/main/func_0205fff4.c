/* func_0205fff4 @ 0x0205fff4, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0205fff4 UnkStruct_0205fff4;
struct UnkStruct_0205fff4 {
    u8 pad_00[8];
    u32 unk_08;
    int unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u8 pad1[8];
    int unk_30;
    u8 pad_34[4];
    u8 unk_38;
};

typedef struct DStruct DStruct;
struct DStruct {
    u8 pad_00[0x30];
    int unk_30;
    u8 pad1[8];
    int unk_3C;
};

extern void func_0205fc3c(UnkStruct_0205fff4 *self);
extern void func_0205fbc4(u32 *a, u32 *b, u32 *c, u32 *d, int e);
extern int func_0205fb28(u32 *a, int b, u32 *c, u32 *d, int e);
extern int func_02034270(void *d, void *src, int a, int b);
extern void func_0203423c(void *d);
extern void func_0206026c(UnkStruct_0205fff4 *self, int arg);
extern int func_020912d4(int size, void *ptr, int a, int b);
extern void func_ov003_0222a56c(void);

void func_0205fff4(UnkStruct_0205fff4 *self)
{
    int zero = 0;
    DStruct D;
    u32 E[3];
    u32 A[3];
    u32 B[3];
    u32 C[3];

    if (self->unk_30 < 15) {
        func_0205fc3c(self);
        if (self->unk_30 == 14) {
            A[0] = self->unk_1C;
            A[1] = self->unk_20;
            A[2] = self->unk_24;
            B[0] = self->unk_08;
            B[1] = self->unk_0C;
            B[2] = self->unk_10;
            func_0205fbc4(A, B, &self->unk_14, &self->unk_18, zero);
        }
        return;
    } else {
        C[0] = self->unk_1C;
        C[1] = self->unk_20;
        C[2] = self->unk_24;
        func_0205fb28(C, self->unk_14, &self->unk_08, &self->unk_18, zero);
        func_02034270(&D, &self->unk_08, 1, 1);
        if (D.unk_30 == 0) {
            goto cleanup;
        }
        {
            int val = D.unk_3C;
            if (val < self->unk_0C) {
                goto cleanup;
            }
            func_0206026c(self, 4);
            self->unk_0C = D.unk_3C - 819;
            E[0] = self->unk_08;
            E[1] = self->unk_0C;
            E[2] = self->unk_10;
            E[1] = val;
            func_020912d4(12, E, 0, 0);
            self->unk_38 = 1;
            func_ov003_0222a56c();
        }
    cleanup:
        func_0203423c(&D);
        return;
    }
}
