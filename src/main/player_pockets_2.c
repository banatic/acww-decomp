/* player_pockets_2: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02098f80 @ 0x02098f80, 0x50 bytes, Thumb
 * func_02098f70 @ 0x02098f70, 0x10 bytes, Thumb
 * func_02098f48 @ 0x02098f48, 0x28 bytes, Thumb
 * func_02098f0c @ 0x02098f0c, 0x3c bytes, Thumb
 * func_02098ee8 @ 0x02098ee8, 0x24 bytes, Thumb
 * func_02098eb8 @ 0x02098eb8, 0x30 bytes, Thumb
 * func_02098e8c @ 0x02098e8c, 0x2c bytes, Thumb
 * func_02098e74 @ 0x02098e74, 0x18 bytes, Thumb
 * func_02098e64 @ 0x02098e64, 0x10 bytes, Thumb
 * func_02098e44 @ 0x02098e44, 0x1e bytes, Thumb
 * func_02098e10 @ 0x02098e10, 0x34 bytes, Thumb
 * func_02098de8 @ 0x02098de8, 0x28 bytes, Thumb
 * func_02098ddc @ 0x02098ddc, 0xc bytes, Thumb
 * func_02098d84 @ 0x02098d84, 0x58 bytes, Thumb
 * func_02098d14 @ 0x02098d14, 0x70 bytes, Thumb
 * func_02098cf8 @ 0x02098cf8, 0x1c bytes, Thumb
 * func_02098cc0 @ 0x02098cc0, 0x38 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02098e8c {
    char pad_00[0xA6C];
    unsigned int unk_A6C;
};

typedef struct {
    char pad_00[0xA68];
    int unk_A68;
} Struct02098cf8;

extern void func_02066650(char *);
extern void func_02065cc8(char *);
extern void func_02098aa0(char *, int, int);
extern int func_02065ec0(void *p);
extern int func_0204c878(u16 *);

void func_02098ee8(unsigned int *base, unsigned int shift, unsigned int val);

void func_02098f80(char *arg)
{
    int i, j;
    for (i = 0; i < 10; i++) {
        func_02066650(arg + (i << 8));
    }
    func_02065cc8(arg + 0xA00);
    for (j = 0; j < 15; j++) {
        *(unsigned short *) (arg + j * 2 + 0xA4A) = 0xFFF1;
    }
    func_02098aa0(arg, 0, 1);
}

int func_02098f70(int r0)
{
    if (r0 >= 0 && r0 < 15) {
        return 1;
    }
    return 0;
}

unsigned short *func_02098f48(void *base, int n)
{
    unsigned short *res = 0;

    if (func_02098f70(n) == 1) {
        res = (unsigned short *) ((char *) base + 0xa4a) + n;
    }

    return res;
}

int func_02098f0c(unsigned short *p0, unsigned short *p1, int p2, int p3)
{
    int result = 0;
    if (func_02098f70(p2) == 1) {
        *(unsigned short *) ((char *) p0 + p2 * 2 + 0xA4A) = *p1;
        func_02098ee8((unsigned int *) p0, p2, p3);
        result = 1;
    }
    return result;
}

void func_02098ee8(unsigned int *base, unsigned int shift, unsigned int val)
{
    unsigned int bit = shift << 1;
    unsigned int mask = 3 << bit;
    unsigned int *addr = base + 0x29B;
    *addr &= ~mask;
    *addr |= (val << bit);
}

int func_02098eb8(int id)
{
    unsigned short *list;
    int i;
    list = func_02098f48((void *) id, 0);
    for (i = 0; i < 15; i++) {
        if (list[i] == 0xfff1) {
            return i;
        }
    }
    return -1;
}

int func_02098e8c(struct UnkStruct_02098e8c *param0, int param1)
{
    int shift = param1 << 1;
    if (func_02098f70(param1) == 1) {
        return (param0->unk_A6C >> shift) & 3;
    }
    return 0;
}

int func_02098e74(void *argument0, int argument1)
{
    int result;
    if (func_02098e8c((struct UnkStruct_02098e8c *) ((void *) argument0), (int) argument1) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_02098e64(int x)
{
    if (x >= 0 && x < 10) {
        return 1;
    } else {
        return 0;
    }
}

int func_02098e44(int param1, int param2)
{
    int result = 0;
    int temp;

    temp = func_02098e64(param2);
    if (temp == 1) {
        result = param1 + (param2 << 8);
    }
    return result;
}

int func_02098e10(int arg)
{
    unsigned char *p;
    int i;
    p = (unsigned char *) func_02098e44(arg, 0);
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            return i;
        }
        p += 0x100;
    }
    return -1;
}

int func_02098de8(int param)
{
    int r4;
    int r5;
    int result;

    r5 = param;
    r4 = func_02098e10(r5);
    if (func_02098e64(r4) == 1) {
        result = func_02098e44(r5, r4);
    } else {
        result = 0;
    }
    return result;
}

unsigned int func_02098ddc(unsigned int r0)
{
    return r0 + 0x0a00;
}

int func_02098d84(void *self)
{
    u16 *p;
    int total;
    int i;

    p = (u16 *) func_02098f48(self, 0);
    total = 0;
    i = 0;
    for (; i < 0xf; i++) {
        unsigned int ok = 0;
        if (*p >= 0x1492 && *p <= 0x14fd) {
            ok = 1;
        }
        if (ok != 0) {
            if (func_02098e8c((struct UnkStruct_02098e8c *) self, i) == 0) {
                total = total + func_0204c878(p);
            }
        }
        p++;
    }
    return total;
}

int func_02098d14(void *data, int base)
{
    unsigned short *p;
    int i;
    int r7;
    int result;
    unsigned short local;

    p = func_02098f48(data, 0);
    local = 0x14fd;
    r7 = func_0204c878((u16 *) (&local));
    result = base * r7;
    i = 0;
    for (; i < 15; p++, i++) {
        unsigned short v = *p;
        if (v == 0xfff1) {
            result += r7;
        } else if (v >= 0x1492 && v <= 0x14fd) {
            if (func_02098e8c((struct UnkStruct_02098e8c *) data, i) == 0) {
                result += r7 - func_0204c878((u16 *) p);
            }
        }
    }
    return result;
}

int func_02098cf8(Struct02098cf8 *obj, int param)
{
    int value = obj->unk_A68;
    if (param) {
        value += func_02098d84((void *) obj);
    }
    return value;
}

int func_02098cc0(int a, int b, int c)
{
    int diff;
    int val;

    diff = 0x1869f - func_02098cf8((Struct02098cf8 *) a, 0);
    val = diff >= 0 ? diff : 0;
    if (b == 1) {
        val += func_02098d14((void *) a, c);
    }
    return val;
}
