/* func_ov068_0226cb00 @ 0x0226cb00, 0xc8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov068_0226cfd4(void *);
extern void func_02019c6c(void *, int, unsigned short);
extern void func_02013c0c(void *);
extern void func_ov068_02266c70(void *, void *);
extern int func_02013894(void *);
extern void func_020138a4(void *, int);
extern void func_ov068_0226c964(void *, int, void *);
extern void func_0202e188(void *);
extern void func_0201cbc4(void *);
typedef struct {
    u32 a;
    u32 b;
} Pair;
extern Pair data_ov068_022770a8;
extern unsigned short data_020c80f8;
int func_ov068_0226cb00(u8 *self, u8 *other)
{
    u8 *ptr;
    u8 **ptr2;
    func_ov068_0226cfd4(other);
    *(Pair *) (other + 0x8b0) = data_ov068_022770a8;
    ptr = self;
    func_02019c6c(other + 0x564, 1, data_020c80f8);
    func_02013c0c(other + 0x558);
    func_ov068_02266c70(other + 0x898, other);
    if (func_02013894(ptr + 0x3c) != 0) {
        func_020138a4(self + 0x3c, 0);
    } else {
        func_ov068_0226c964(self, 0, other);
        *((short *) (self + 0xd8)) = -1;
        *((short *) (self + 0xda)) = 0;
    }
    func_0202e188(other);
    *((u8 *) (other + 0x561)) = 1;
    *((u8 *) (other + 0x562)) = 1;
    *((u32 *) (self + 0xf8)) = -1;
    ptr2 = &other;
    *((u8 *) (other + 0x9f0)) = 1;
    func_0201cbc4((*ptr2) + 0x83c);
    return 1;
}
