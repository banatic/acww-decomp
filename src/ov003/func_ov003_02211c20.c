/* func_ov003_02211c20 @ 0x02211c20, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(void *, void *);
extern int func_0200f290(void *, int);
extern void func_0200f268(void *, int);
extern int func_ov003_02221294(void *, void *, int);
extern int func_ov003_02220f40(void *, void *, int);

typedef struct {
    int x, y, z;
} Vec;
struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};
struct UnkStruct_02211c20_2 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x704 - 0x90];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    struct S7d4 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    void *unk_800;
};
struct UnkStruct_02211c20 {
    Vec a, b, c, d;
};

extern unsigned char data_020ccf94[];

void func_ov003_02211c20(struct UnkStruct_02211c20_2 *o)
{
    struct UnkStruct_02211c20 t;
    struct S7d4 *p;
    if (func_02073908(*(void **) data_020ccf94, o->unk_800) != 0) {
        return;
    }
    if (func_0200f290(o, 0x1c) == 0) {
        return;
    }
    p = &o->unk_7D4;
    t.a.x = p->unk_04;
    t.a.y = p->unk_08;
    t.a.z = p->unk_0C;
    if (o->unk_704 == 0x4b) {
        t.b.x = t.a.x;
        t.b.y = t.a.y;
        t.b.z = t.a.z;
        func_ov003_02221294(o->unk_800, &t.b, 0);
    } else {
        t.c.x = t.a.x;
        t.c.y = t.a.y;
        t.c.z = t.a.z;
        func_ov003_02220f40(o->unk_800, &t.c, o->unk_8E);
        t.d.x = t.a.x;
        t.d.y = t.a.y;
        t.d.z = t.a.z;
        func_ov003_02221294(o->unk_800, &t.d, 0);
    }
    func_0200f268(o, 0x1c);
}
