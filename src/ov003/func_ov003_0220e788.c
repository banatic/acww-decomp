/* func_ov003_0220e788 @ 0x0220e788, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *, int);
extern void func_0200f268(void *, int);
extern void func_ov003_02221228(void *, void *);
extern void func_ov003_02220b44(void *, void *);
extern void func_0209129c(int);

typedef struct {
    int x, y, z;
} Vec;
struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
};
struct UnkStruct_0220e788_2 {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x7d4 - 0x68];
    struct S7d4 unk_7D4;
    char pad_7E0[0x800 - 0x7e0];
    void *unk_800;
};
struct UnkStruct_0220e788 {
    Vec a, b, c;
};

void func_ov003_0220e788(struct UnkStruct_0220e788_2 *o, int k)
{
    struct UnkStruct_0220e788 t;
    struct S7d4 *q = &o->unk_7D4;
    {
        Vec *pos;
        int z = q->unk_04;
        int y = o->pos.y;
        t.a.x = q->unk_00;
        t.a.y = y;
        t.a.z = z;
        pos = &o->pos;
        o->pos.x = t.a.x;
        pos->y = t.a.y;
        pos->z = t.a.z;
    }
    if (func_0200f290(o, 0x12) != 0) {
        if (k == 0x74 || k == 0x75) {
            Vec *pos = &o->pos;
            t.b.x = o->pos.x;
            t.b.y = pos->y;
            t.b.z = pos->z;
            func_ov003_02221228(o->unk_800, &t.b);
        }
        func_0200f268(o, 0x12);
    }
    if (k != 0x74 && k != 0x75) {
        Vec *pos = &o->pos;
        t.c.x = o->pos.x;
        t.c.y = pos->y;
        t.c.z = pos->z;
        func_ov003_02220b44(o->unk_800, &t.c);
    }
    if (k != 0x74) {
        if (q->unk_08 != -1) {
            func_0209129c(q->unk_08);
        }
    }
}
