/* func_ov004_0221cc14 @ 0x0221cc14, 0x134 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x830];
    void *unk_830;
    char pad_834[0x898 - 0x834];
    int unk_898;
    char pad_89C[0x8a0 - 0x89c];
    char unk_8A0;
    char pad_8A1[0x8e0 - 0x8a1];
    int unk_8E0;
} UnkStruct_0221cc14;

#define OBJ (*(UnkStruct_0221cc14 **) (self + 0x1a4))

extern void *func_0208150c(void *);
extern void func_0200366c(void *a, void *b, int c, void *d);
extern int func_020644cc(int);
extern int func_ov004_0221d02c(void *self);
extern int func_ov004_0221cff8(void *self);
extern void func_ov004_0221d014(void *self);
extern void *func_020826a8(int i);
extern int func_020826cc(void);
extern void func_02015e10(void *addr, void *a, int flag);
extern void func_02015de4(void *self, u16 *buf, int a, int b);

extern char data_ov004_02257a6c;
extern char data_ov004_02253734;

void func_ov004_0221cc14(char *self, void *out0)
{
    char *out = (char *) out0;
    int mode;
    int i;

    func_0200366c(func_0208150c(OBJ->unk_830), &data_ov004_02257a6c, 0x28, &data_ov004_02253734);
    *(void **) out = &data_ov004_02257a6c;

    if (OBJ->unk_898 == 9) {
        *(u8 *) (out + 4) = (u8) func_020644cc(2);
        return;
    }

    mode = 3;
    if (func_ov004_0221d02c(self) != 0) {
        mode = 1;
    } else if (func_ov004_0221cff8(self) != 0) {
        mode = 2;
    }
    func_ov004_0221d014(self);

    switch (mode) {
        case 1:
            *(u8 *) (out + 4) = (u8) (func_020644cc(2) + 2);
            break;
        case 2:
            *(u8 *) (out + 4) = (u8) (func_020644cc(4) + 0x13);
            break;
        default:
            *(u8 *) (out + 4) = (u8) (func_020644cc(2) + 4);
            break;
    }

    if (OBJ->unk_8E0 == 0) {
        return;
    }
    if (OBJ != 0 && OBJ->unk_830 != 0) {
        func_02015e10((char *) OBJ + 0x8a0, func_0208150c(OBJ->unk_830), 1);
    }

    {
        UnkStruct_0221cc14 **objp;
        i = 0;
        objp = (UnkStruct_0221cc14 **) (self + 0x1a4);
        for (; i < func_020826cc(); i++) {
            void *cand = func_020826a8(i);
            if (cand != 0 && cand != (void *) *objp) {
                func_02015e10((char *) OBJ + 0x8a0, func_0208150c(((UnkStruct_0221cc14 *) cand)->unk_830), 0);
                break;
            }
        }
    }

    {
        u16 buf = 0x1100;
        func_02015de4(self, &buf, 0, 7);
        func_02015de4(self, &buf, 1, 7);
    }
}
