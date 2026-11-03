/* rmo_object_slots: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c598 @ 0x0222c598, 0x1c bytes, Thumb
 * func_ov004_0222c590 @ 0x0222c590, 0x6 bytes, Thumb
 * func_ov004_0222c574 @ 0x0222c574, 0x1a bytes, Thumb
 * func_ov004_0222c558 @ 0x0222c558, 0x1a bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[234];
    unsigned char unk_EA;
} UnkStruct_0222c590;

extern void func_ov004_0222c5b4(char *a, char *b);
extern int func_0209d3d0(unsigned int arg0);
extern int func_0209d3bc(unsigned int index, unsigned int value);

void func_ov004_0222c598(char *self)
{
    func_ov004_0222c5b4(self + 0x1a4, self + 0x248);
}

void func_ov004_0222c590(UnkStruct_0222c590 *p, unsigned char v)
{
    p->unk_EA = v;
}

int func_ov004_0222c574(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0xea) != 0xff) {
        return func_0209d3d0(*(u8 *) (self + 0xea));
    }
    return 0x0;
}

int func_ov004_0222c558(char *self, unsigned int value)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0xea) != 0xff) {
        return func_0209d3bc(*(u8 *) (self + 0xea), value);
    }
    return 0x0;
}
