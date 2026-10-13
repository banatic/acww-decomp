/* func_ov004_0223ebf0 @ 0x0223ebf0, 0xd8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223ebf0 {
    u8 flag;
    u8 pad_01;
    short v;
};
extern struct UnkStruct_0223ebf0 data_ov004_02256308[];
extern char data_ov004_02259a34[];
extern void func_020e9898(void *);
extern void func_02055008(void *);
extern void func_0205502c(void *);
extern void func_02004280(void *);
extern void func_0209d090(void *);
extern void func_0209d200(void *, void *);

void func_ov004_0223ebf0(char *self, int i)
{
    char *p;
    signed char c;
    int zero;
    if (i < 0 || i >= 0x20) {
        return;
    }
    p = data_ov004_02259a34 + 0x2d8 * i;
    c = *(signed char *) (p + 0x196);
    if (c == 0x38) {
        func_020e9898(*(void **) (self + 0x19c));
        *(int *) (self + 0x19c) = 0;
    } else if (c == 0x23) {
        func_020e9898(*(void **) (self + 0x198));
        *(int *) (self + 0x198) = 0;
    }
    if (data_ov004_02256308[c].flag != 0) {
        func_02055008(p + 0xb0);
    } else {
        func_0205502c(p + 0xb0);
    }
    *(int *) (p + 0x18) = 0;
    *(int *) (p + 0x1c) = 0;
    func_02004280(p + 0x24);
    zero = 0;
    *(signed char *) (p + 0x196) = (signed char) ~zero;
    *(short *) (p + 0x192) = (short) zero;
    *(int *) (p + 0x198) = zero;
    *(short *) (p + 0x168) = (short) zero;
    *(short *) (p + 0x172) = 0x19;
    func_0209d090(p + 0x288);
    func_0209d200(self + 0x180, p + 0x284);
    *(int *) (p + 0x2d4) = 0;
}
