/* func_020575e4 @ 0x020575e4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02057640(void *p0, void *p1, void *p2, void *p3);
extern void func_02057730(void *dst, void *src);
extern void func_02056fcc(void *p0, int p1, int p2, int p3, int p4);
extern void func_02057538(void *p);

typedef struct {
    u8 pad_00[0x50];
    void *unk_50;
    u8 unk_54[0x11];
    u8 unk_65[0x13];
    void *unk_78;
    void *unk_7C;
    u8 pad_80[0x8c - 0x80];
    u8 unk_8C;
} UnkStruct_020575e4;

int func_020575e4(UnkStruct_020575e4 *p, void *b, void *c, void *d, void *e, void *f, u8 g)
{
    func_02057640(p, b, c, d);
    p->unk_8C = g;
    func_02057730(p->unk_54, c);
    func_02057730(p->unk_65, d);
    p->unk_50 = b;
    p->unk_78 = e;
    p->unk_7C = f;
    func_02056fcc(p, *(u16 *) ((u8 *) f + 4), 0, 0x1000, 0);
    func_02057538(p);
    return 1;
}
