/* birthday_villager_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221d4f4 @ 0x0221d4f4, 0x4c bytes, Thumb
 * func_ov004_0221d4e8 @ 0x0221d4e8, 0xc bytes, Thumb
 * func_ov004_0221d4c0 @ 0x0221d4c0, 0x28 bytes, Thumb
 * func_ov004_0221d468 @ 0x0221d468, 0x58 bytes, Thumb
 */

#include "types.h"

extern void *func_020edf70(int size);
extern void *func_0202e8e4(void *p);
extern void *func_0202decc(void *p);
extern int data_ov004_02253674;
extern int data_ov004_022535e4;
extern unsigned int data_ov004_02257a18;
extern int func_ov004_0221cff8(char *self);
extern int func_0204bcdc(void *it);
extern int func_0204bc64(void *it);

void *func_ov004_0221d4f4(void)
{
    char *o = (char *) func_020edf70(0xa70);
    if (o != 0) {
        func_0202e8e4(o);
        *(int *) o = (int) &data_ov004_02253674;
        func_0202decc(o + 0x8a0);
        *(int *) (o + 0x8a0) = (int) &data_ov004_022535e4;
        *(u16 *) (o + 0xa50) = 0xfff1;
    }
    return o;
}

unsigned int func_ov004_0221d4e8(void)
{
    return data_ov004_02257a18;
}

int func_ov004_0221d4c0(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) ((void **) &data_ov004_02257a18)) != 0x0) {
        return func_ov004_0221cff8((char *) *(int *) ((char *) ((void **) &data_ov004_02257a18)) + 0x8a0);
    }
    return 0x0;
}

int func_ov004_0221d468(void *it, int k)
{
    unsigned short empty;
    int ok;

    if (k == 0) {
        if (func_0204bcdc(it) != 0) {
            empty = 0xfff1;
            ok = (func_0204bc64(it) == func_0204bc64(&empty)) ? 1 : 0;
        } else {
            ok = (*(unsigned short *) it == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            return 1;
        }
    }
    return 0;
}
