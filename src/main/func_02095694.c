/* func_02095694 @ 0x02095694, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02096718(void *x);
extern void *func_020984fc(void *x);
extern unsigned int func_02062230(void);
extern void func_020621d4(void *dst, unsigned int value);
extern void func_0209971c(void *x, void *p);
extern void func_0205eb8c(void *base, void *p, void *arg);
extern void func_02010934(void *base);
extern void func_0205ea60(void *base);

struct UnkStruct_02095694 {
    u8 pad_00[0x5a0];
    s32 unk_5A0;
    u8 pad_5A4[0x704 - 0x5a0 - 4];
    s32 unk_704;
};

int func_02095694(unsigned int n, void *x)
{
    struct UnkStruct_02095694 *obj;
    u16 v0;
    u16 v1;
    u16 v2;
    u16 v3;
    u16 v4;

    obj = (struct UnkStruct_02095694 *) func_02096718(x);
    if (obj == 0) {
        return 0;
    }

    x = func_020984fc(x);

    if (obj->unk_704 >= 0xa1) {
        if (n == 0 || func_02062230() < n) {
            v1 = 0xfff1;
            func_0209971c(x, &v1);
        } else {
            func_020621d4(&v2, n - 1);
            func_0209971c(x, &v2);
        }
        return 0;
    } else {
        if (n == 0 || func_02062230() < n) {
            v3 = 0xfff1;
            func_0209971c(x, &v3);
            v4 = 0xfff1;
            func_0205eb8c(&obj->unk_5A0, &v4, 0);
            func_02010934(obj);
        } else {
            func_020621d4(&v0, n - 1);
            func_0209971c(x, &v0);
            func_0205eb8c(&obj->unk_5A0, &v0, x);
            func_02010934(obj);
            func_0205ea60(&obj->unk_5A0);
        }
        return 1;
    }
}
