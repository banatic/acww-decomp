/* func_ov003_0220f538 @ 0x0220f538, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
} UnkStruct_0220f538;

typedef struct {
    u8 pad_00[0xc];
    UnkStruct_0220f538 sub;
    u8 pad_12[0xa];
} Buf;

extern unsigned int func_0200e92c(Buf *);
extern void func_0200e90c(Buf *, int, unsigned int, short);
extern void func_ov003_0220f57c(UnkStruct_0220f538 *, Vec);
extern void *func_0200e894(void *, Buf *);
extern int func_0200e91c(Buf *);

void *func_ov003_0220f538(void *a0, Vec v, unsigned int a4, short a5)
{
    Buf buf;
    void *ret;

    func_0200e92c(&buf);
    func_0200e90c(&buf, 0x6a, a4, a5);
    func_ov003_0220f57c(&buf.sub, v);
    ret = func_0200e894(a0, &buf);
    func_0200e91c(&buf);
    return ret;
}
