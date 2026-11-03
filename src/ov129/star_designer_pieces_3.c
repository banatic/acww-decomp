/* star_designer_pieces_3: 5 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229bf88 @ 0x0229bf88, 0x34 bytes, Thumb
 * func_ov129_0229bf54 @ 0x0229bf54, 0x34 bytes, Thumb
 * func_ov129_0229bf30 @ 0x0229bf30, 0x24 bytes, Thumb
 * func_ov129_0229bf10 @ 0x0229bf10, 0x20 bytes, Thumb
 * func_ov129_0229bee4 @ 0x0229bee4, 0x2a bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x2f78];
    u16 table[16];
} UnkStruct_0229bf88;

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
} UnkStruct_0229bf54;

extern void func_ov129_0229be04(UnkStruct_0229bf54 *s, unsigned char val);
extern void func_ov127_02299a00(unsigned char *p, int idx, unsigned char byte);
extern unsigned char data_ov129_0229dae0[];
extern void func_ov129_0229c0e8(int a);

void func_ov129_0229bf88(UnkStruct_0229bf88 *self)
{
    int i;
    u16 *q = self->table;

    for (i = 0; i < 16; i++) {
        u16 v = *q;
        if (v != 0xffff) {
            ((u8 *) self + v)[0x2f98] = 2;
        }
        q++;
    }
}

void func_ov129_0229bf54(UnkStruct_0229bf54 *s)
{
    unsigned char flag = s->b1;
    switch (flag) {
        case 0:
            break;
        case 1:
            func_ov129_0229be04(s, s->b2);
            break;
        case 2:
            func_ov129_0229be04(s, s->b3);
            break;
    }
}

void func_ov129_0229bf30(unsigned char *p, int idx)
{
    func_ov127_02299a00(p + 0x734, idx, data_ov129_0229dae0[(p + idx)[0x2f98]]);
}

void func_ov129_0229bf10(int param)
{
    int i;
    for (i = 0; i < 454; i++) {
        func_ov129_0229bf30((unsigned char *) param, i);
    }
}

void func_ov129_0229bee4(int a, int b)
{
    func_ov129_0229c0e8(a);
    func_ov129_0229bf88((UnkStruct_0229bf88 *) a);
    if (b != 0) {
        func_ov129_0229bf54((UnkStruct_0229bf54 *) a);
    }
    func_ov129_0229bf10(a);
}
