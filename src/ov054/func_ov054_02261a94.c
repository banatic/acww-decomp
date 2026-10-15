/* func_ov054_02261a94 @ 0x02261a94, 0x64 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261a94 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    void *unk_B0;
} UnkStruct_02261a94;

typedef struct Elem {
    int a;
    int b;
    int c;
} Elem;

extern Elem data_ov054_02262fac[];

extern unsigned char func_ov054_02260484(void *receiver);
extern int func_0206fc6c(void);
extern void func_ov054_02261cc4(UnkStruct_02261a94 *self, int a);
extern void func_0206844c(int h, u8 *p, int k);

void func_ov054_02261a94(UnkStruct_02261a94 *self)
{
    u8 arg;
    int h;
    int code;
    int k;
    void *p;

    h = self->unk_40;
    p = self->unk_B0;
    k = data_ov054_02262fac[*(int *) ((char *) p + 0x808)].a;
    if (func_ov054_02260484(p) != 0) {
        if (func_0206fc6c() != 0) {
            code = 0x63;
        } else {
            code = 0x64;
        }
    } else {
        if (func_0206fc6c() != 0) {
            code = 0x5d;
        } else {
            code = 0x5e;
        }
    }
    func_ov054_02261cc4(self, 0);
    arg = (u8) code;
    func_0206844c(h, &arg, k);
}
