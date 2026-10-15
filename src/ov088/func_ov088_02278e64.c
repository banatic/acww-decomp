/* func_ov088_02278e64 @ 0x02278e64, 0xa8 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278e64 {
    char pad_00[0x40];
    int *unk_40;
    char pad_44[0xb8 - 0x44];
    char *unk_B8;
} UnkStruct_02278e64;

extern int func_02013a94(char *p);
extern int func_020683e4(int *h, int a, u8 *p, int k);
extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void func_ov088_02278a54(char *p, int a, int b);
extern void func_0206844c(int *h, u8 *p, int k);
extern int func_0202ea80(int a, int b);
extern void func_ov088_02278f0c(UnkStruct_02278e64 *self, int a);
extern int data_ov088_02279da8;
extern int data_ov088_02279d98;

void func_ov088_02278e64(UnkStruct_02278e64 *self)
{
    u8 m[2];
    int *h;

    h = self->unk_40;
    if (h[1] == 5) {
        *(u8 *) (self->unk_B8 + 0x739) = 0x14;
        if (func_02013a94(self->unk_B8) != -1) {
            m[1] = 0x17;
            func_020683e4(self->unk_40, 0, &m[1], (int) &data_ov088_02279da8);
            *(u8 *) (self->unk_B8 + 0x739) = 0;
            *(u8 *) (self->unk_B8 + 0x738) = 0x14;
            func_02098ff8(func_020984e8(), 0x10);
            m[0] = 0xc;
            func_ov088_02278a54(self->unk_B8, 0, 0x17);
            func_0206844c(h, &m[0], (int) &data_ov088_02279d98);
            func_0202ea80(0xe, 1);
            func_ov088_02278f0c(self, 4);
        }
    }
}
