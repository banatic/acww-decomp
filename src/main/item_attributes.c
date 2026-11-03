/* item_attributes: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209b850 @ 0x0209b850, 0x20 bytes, Thumb
 * func_0209b7ac @ 0x0209b7ac, 0xa4 bytes, Thumb
 * func_0209b750 @ 0x0209b750, 0x5c bytes, Thumb
 * func_0209b6c0 @ 0x0209b6c0, 0x90 bytes, Thumb
 */

#include "types.h"

extern unsigned char data_020d1a60[];
extern void MI_CpuFill8(void *dst, int val, int len);
extern int func_020535f0(const unsigned short *ptr);
extern int func_020644cc(int);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_020539e4(u16 *p);
extern int func_02053cf0(int t);
extern int func_02053cbc(int t);
extern int func_02053a88(u16 *p);
extern int func_02053b6c(u16 *p);
extern int func_02053c68(u16 *p);

int func_0209b850(int r0)
{
    int r3;
    int r1;

    r3 = 0;
    while (r3 < 10) {
        r1 = data_020d1a60[r3];
        if (r0 == r1) {
            return r3;
        }
        r3++;
    }
    return -1;
}

unsigned char func_0209b7ac(unsigned short *ptr, int count)
{
    int rem = 10;
    int flag = 0;
    int j0 = 0;
    unsigned char local[10];
    int i, j, k, n;

    MI_CpuFill8(local, 0, rem);
    for (i = 0; i < count; i++, ptr++) {
        int ok = flag;
        if ((unsigned int) *ptr >= 0x450cU && (unsigned int) *ptr <= 0x45dbU) {
            ok = 1;
        }
        if (ok) {
            for (j = j0; j < 10; j++) {
                if (func_020535f0(ptr) == data_020d1a60[j] && local[j] == 0) {
                    local[j] = 1;
                    rem--;
                    break;
                }
            }
        }
    }
    n = func_020644cc(rem);
    k = 0;
    while (n >= 0) {
        if (local[k] == 0) {
            if (n == 0) {
                break;
            }
            n--;
            k++;
        } else {
            k++;
        }
    }
    return data_020d1a60[k];
}

void func_0209b750(unsigned short *out, unsigned int match, unsigned int add)
{
    unsigned int i;
    unsigned int idx;
    unsigned short tmp;

    *out = 0xFFF1;
    tmp = 0xFFF1;
    i = 0;

    while (i < 0x34) {
        tmp = (i < 0x34) ? (i * 4 + 0x450C) : 0x450C;
        if (func_020535f0((const unsigned short *) (&tmp)) == match) {
            idx = i + add;
            *out = (idx < 0x34) ? (idx * 4 + 0x450C) : 0x450C;
            break;
        }
        i++;
    }
}

int func_0209b6c0(u16 *p, int kind, int val)
{
    int res;
    int t;

    res = 0;
    if (func_0204bcdc(p) != 0) {
        switch (kind) {
            case 0:
                if (val == func_020539e4(p)) {
                    res = 2;
                }
                break;
            case 1:
                t = func_0204bc64(p);
                if (val == func_02053cf0(t)) {
                    res = 1;
                }
                if (val == func_02053cbc(t)) {
                    res++;
                }
                break;
            case 2:
                if (val == func_02053a88(p)) {
                    res = 2;
                }
                break;
            case 3:
                if (val == func_02053b6c(p)) {
                    res = 2;
                }
                break;
            case 4:
                if (val == func_02053c68(p)) {
                    res = 2;
                }
                break;
        }
    }
    return res;
}
