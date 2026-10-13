/* func_0200f554 @ 0x0200f554, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec unk_5C;
    Vec unk_68;
    char pad_74[0x8e - 0x74];
    short unk_8E;
} UnkStruct_0200f554;

extern int func_0200f5e4(UnkStruct_0200f554 *o, Vec *a, short *b);
extern int func_020ea990(Vec *a, Vec *b);
extern void func_0200fb7c(UnkStruct_0200f554 *o, int x, int z, short b);

int func_0200f554(UnkStruct_0200f554 *o)
{
    short b;
    Vec a;
    Vec *p;
    Vec *q;

    if (func_0200f5e4(o, &a, &b)) {
        p = &o->unk_5C;
        if (p->x == a.x && p->z == a.z && b == o->unk_8E) {
            return 1;
        }
        if (func_020ea990(p, &a) >= 0xe000) {
            q = &o->unk_68;
            q->x = a.x;
            q->y = a.y;
            q->z = a.z;
            p->x = q->x;
            p->y = q->y;
            p->z = q->z;
            o->unk_8E = b;
            return 0;
        } else {
            func_0200fb7c(o, a.x, a.z, b);
            return 0;
        }
    } else {
        return 1;
    }
}
