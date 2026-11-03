/* giraffe_talk_2: 3 functions, module ov070
 * mwccarm 1.2/base -O4,s
 * func_ov070_02279778 @ 0x02279778, 0xa8 bytes, Thumb
 * func_ov070_02279758 @ 0x02279758, 0x1e bytes, Thumb
 * func_ov070_02279724 @ 0x02279724, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02279778 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    char pad_B8[0xc0 - 0xb8];
    int unk_C0;
} UnkStruct_02279778;

extern int func_0206fc6c(void);
extern int func_0206f83c(void);
extern void func_0201b420(int a, int b);
extern void func_0208b514(unsigned int context);
extern int func_0208602c(void);
extern void func_020860f0(int a, int b);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov070_02279d58;
extern int func_020644cc(int);

void func_ov070_02279778(UnkStruct_02279778 *self)
{
    u8 code;
    int h;
    int v;

    h = self->unk_40;
    code = 0x4b;
    self->unk_C0 = 0;
    v = func_0206fc6c();
    if (v != 0) {
        self->unk_C0 = func_0206f83c();
        code = 0x2d;
        v = self->unk_C0;
        if (v > 1000 && v <= 2000) {
            code = 0x2e;
        } else if (v > 2000 && v <= 4000) {
            code = 0x2f;
        } else if (v > 4000) {
            code = 0x30;
        }
        func_0201b420(self->unk_B4, self->unk_C0);
    } else {
        func_0208b514(v);
        func_020860f0(func_0208602c(), 0xa);
    }
    func_0206844c(h, &code, (int) &data_ov070_02279d58);
}

int func_ov070_02279758(int unused, const unsigned char *s, int n)
{
    int count = 0;
    int i = 0;
    while (i < n) {
        if (*s == 0) {
            count++;
        }
        s++;
        i++;
    }
    return count;
}

int func_ov070_02279724(int a, unsigned char *str, int len)
{
    int i;
    int result;
    unsigned char *p;

    a = func_ov070_02279758(a, (const unsigned char *) str, len);
    result = 0;
    a = func_020644cc(a);

    p = str;
    for (i = 0; i < len; p++, i++) {
        if (*p == 0) {
            if (a == 0) {
                result = i;
                break;
            }
            a--;
        }
    }

    return result;
}
