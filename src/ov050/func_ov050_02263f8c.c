/* func_ov050_02263f8c @ 0x02263f8c, 0x58 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, unsigned short);
extern int func_0201c2c8(void *, int);
extern void func_0201aff4(void *, int);
extern int func_0203e0a8(void *, int);

typedef struct {
    u8 pad_00[0x350];
    u8 unk_350;
    u8 pad_351[0x564 - 0x350 - 1];
    u8 unk_564;
    u8 pad_565[0x730 - 0x564 - 1];
    u16 unk_730;
} UnkStruct_02263f8c;

int func_ov050_02263f8c(UnkStruct_02263f8c *p)
{
    if (func_02019e00(&p->unk_564) == 3) {
        if (func_02019de8(&p->unk_564) != 0) {
            func_02019c6c(&p->unk_564, 1, p->unk_730);
        }
    }
    {
        int tmp = func_0201c2c8(p, 4);
        func_0201aff4(&p->unk_350, tmp);
    }
    func_0203e0a8(p, 0);
    return 1;
}
