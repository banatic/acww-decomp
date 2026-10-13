/* func_ov003_022344c8 @ 0x022344c8, 0x138 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022344c8;
extern UnkStruct_022344c8 *data_020ccf94;

extern int func_020644cc(int n);
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02233c70(int a, int b);

void func_ov003_022344c8(char *self, short *pn)
{
    int *p;
    int r;
    short n;
    u8 s;
    int a;
    int base;
    int t;
    int *s2;
    int *d2;

    p = (int *) (self + 0x204);
    r = func_020644cc(0x64);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
        d2 = (int *) (self + 0x1d4);
        if (d2[0] != p[0] || d2[2] != p[2]) {
            *(u8 *) (self + 0x251) = 4;
            *pn = 0;
            return;
        }
    } else {
        n = *pn;
        if ((n == 0 && r > 0x5f) || (n == 0xa && r > 0x50) || ((n == 0x14 || n == 0x1e) && r > 0x32) || n >= 0x28) {
            s = *(u8 *) (self + 0x251);
            if (s != 0xd && s != 0xe) {
                a = *(s8 *) (self + 0x24d) == 0x17 ? 5 : 0xd;
                base = *(short *) (self + 0x23a);
                t = func_ov003_02233c70((u8) a, 1);
                *(short *) (self + 0x240) = t + base;
                s2 = (int *) (self + 0x204);
                d2 = (int *) (self + 0x1d4);
                d2[0] = s2[0];
                d2[1] = s2[1];
                d2[2] = s2[2];
            }
            *(u8 *) (self + 0x251) = 3;
            *(int *) (self + 0x21c) |= 0xf00;
            *pn = 0;
            return;
        }
    }
    if (*pn % 0xa < 5) {
        if (p[1] < *(int *) (self + 0x228) + 0x800) {
            p[1] = p[1] + 0x80;
        }
    } else {
        if (p[1] > *(int *) (self + 0x228) - 0x800) {
            p[1] = p[1] - 0x80;
        }
    }
    *pn = *pn + 1;
}
