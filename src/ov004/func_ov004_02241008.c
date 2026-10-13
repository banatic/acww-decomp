/* func_ov004_02241008 @ 0x02241008, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

// Built at -O1,s like func_ov004_02240fc0 next to it.
extern long FX_MulFunc(long, long);
typedef struct {
    long x, y;
} UnkStruct_02241008;
typedef struct {
    unsigned char pad_00[0x58];
    UnkStruct_02241008 lo;
    UnkStruct_02241008 hi;
} UnkStruct_02241008_2;
void func_ov004_02241008(UnkStruct_02241008_2 *o, UnkStruct_02241008 *a, UnkStruct_02241008 *b)
{
    long t1, t2;
    UnkStruct_02241008 *p, *q;
    t1 = FX_MulFunc(a->y << 12, 0x100);
    t2 = FX_MulFunc(a->x << 12, 0x100);
    p = &o->lo;
    o->lo.x = t2;
    p->y = t1;
    t1 = FX_MulFunc(b->y << 12, 0x100);
    t2 = FX_MulFunc(b->x << 12, 0x100);
    q = &o->hi;
    o->hi.x = t2;
    q->y = t1;
}
