/* func_ov003_02210c24 @ 0x02210c24, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
} UnkStruct_02210c24;

typedef struct {
    u8 pad_00[0xc];
    UnkStruct_02210c24 sub;
    u8 pad_12[0xa];
} Buf;

extern unsigned int func_0200e92c(Buf *);
extern void func_0200e90c(Buf *, int, u32, short);
extern void *func_0200e894(void *, Buf *);
extern int func_0200e91c(Buf *);

void *func_ov003_02210c24(void *a0, u32 a1, u32 *a2, u16 a3, u32 a4, short a5)
{
    Buf buf;
    UnkStruct_02210c24 *p;
    void *ret;

    func_0200e92c(&buf);
    p = &buf.sub;
    func_0200e90c(&buf, 0x61, a4, a5);
    p->unk_00 = a3;
    p->unk_04 = (u8) a1;
    p->unk_02 = (u8) a2[0];
    p->unk_03 = (u8) a2[1];
    ret = func_0200e894(a0, &buf);
    func_0200e91c(&buf);
    return ret;
}
