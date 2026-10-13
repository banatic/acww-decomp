/* func_ov003_022108c0 @ 0x022108c0, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(void *, void *);
extern int func_0200f290(void *, int);
extern void func_0200f268(void *, int);
extern void func_ov003_022211bc(void *, void *);
extern void func_ov003_02221150(void *, void *);

typedef struct {
    int x, y, z;
} Vec;
struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};
struct UnkStruct_022108c0_2 {
    char pad_00[0x7d4];
    struct S7d4 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    void *unk_800;
};
struct UnkStruct_022108c0 {
    Vec a, b, c;
};

extern unsigned char data_020ccf94[];

void func_ov003_022108c0(struct UnkStruct_022108c0_2 *o)
{
    struct UnkStruct_022108c0 t;
    void *g = *(void **) data_020ccf94;
    struct S7d4 *p;
    if (func_02073908(g, o->unk_800) != 0) {
        return;
    }
    if (func_0200f290(o, 0x1c) == 0) {
        return;
    }
    p = &o->unk_7D4;
    t.a.x = p->unk_04;
    t.a.y = p->unk_08;
    t.a.z = p->unk_0C;
    if (func_02073908(g, o->unk_800) != 0) {
        t.b.x = t.a.x;
        t.b.y = t.a.y;
        t.b.z = t.a.z;
        func_ov003_022211bc(o->unk_800, &t.b);
    } else {
        t.c.x = t.a.x;
        t.c.y = t.a.y;
        t.c.z = t.a.z;
        func_ov003_02221150(o->unk_800, &t.c);
    }
    func_0200f268(o, 0x1c);
}
