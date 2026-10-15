/* func_ov082_022790a8 @ 0x022790a8, 0xc0 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022790a8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
    char pad_B4[0xc4 - 0xb4];
    u16 unk_C4;
} UnkStruct_022790a8;

extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern int func_02086564(u16 *p);
extern int func_02015330(UnkStruct_022790a8 *self, u16 *p, int a, int b, int c);
extern void func_ov082_02279190(UnkStruct_022790a8 *self, int a);
extern void func_02015de4(UnkStruct_022790a8 *self, u16 *p, int a, int b);
extern void func_02015fb0(UnkStruct_022790a8 *self, int a, int b, int c, int d, int e);
extern void func_0209a050(int a);
extern int func_020155cc(UnkStruct_022790a8 *self);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov082_022798c8;

void func_ov082_022790a8(UnkStruct_022790a8 *self)
{
    u8 code;
    int h;
    int t;

    h = self->unk_40;
    self->unk_C4 = 0xfff1;
    *(int *) (self->unk_B0 + 0x724) = 0;
    code = 0xc;
    if (func_0206fc6c() != 0) {
        t = func_0206fc8c();
        self->unk_C4 = (u16) func_0209a034(t);
        *(int *) (self->unk_B0 + 0x724) = func_02086564(&self->unk_C4);
        func_02015330(self, &self->unk_C4, 0, 4, 0);
        func_ov082_02279190(self, 1);
        func_02015de4(self, &self->unk_C4, 2, 7);
        func_02015fb0(self, *(int *) (self->unk_B0 + 0x724) >> 12, 4, 3, 0, 0);
        if (t >= 0) {
            func_0209a050(t);
        }
        code = 0xd;
    } else {
        func_020155cc(self);
    }
    func_0206844c(h, &code, (int) &data_ov082_022798c8);
}
