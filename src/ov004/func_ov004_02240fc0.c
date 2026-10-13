/* func_ov004_02240fc0 @ 0x02240fc0, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    long x, y;
} UnkStruct_02240fc0;
typedef struct {
    long a, unk_04, b;
} UnkStruct_02240fc0_2;
typedef struct {
    unsigned char pad_00[0x58];
    UnkStruct_02240fc0 lo;
    UnkStruct_02240fc0 hi;
} UnkStruct_02240fc0_3;
void func_ov004_02240fc0(UnkStruct_02240fc0_3 *o)
{
    UnkStruct_02240fc0_2 *s = (UnkStruct_02240fc0_2 *) ((char *) o + 0x2c8);
    long dy, ey;
    UnkStruct_02240fc0 *p, *q;
    dy = s->b - 0x200;
    p = &o->lo;
    o->lo.x = s->a - 0x900;
    p->y = dy;
    ey = s->b + 0x500;
    q = &o->hi;
    o->hi.x = s->a + 0x900;
    q->y = ey;
}
