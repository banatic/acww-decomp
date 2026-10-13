/* func_ov003_0220fd04 @ 0x0220fd04, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ed8(int, int);
extern void func_ov003_0220fd90(void *, int, void *);
extern void func_020109a0(void *, int, int, int);
extern void func_ov003_02220db4(void *, void *);
extern void func_0200f268(void *, int);
extern void func_0200f328(void *, int);
extern void func_0200f27c(void *, int);

typedef struct {
    int x, y, z;
} Vec;
struct UnkStruct_0220fd04 {
    int x, y, z;
};
struct UnkStruct_0220fd04_2 {
    char pad_00[0xc];
    struct UnkStruct_0220fd04 s;
};
struct UnkStruct_0220fd04_4 {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x7d4 - 0x68];
    char unk_7D4[1];
    char pad_7D5[0x800 - 0x7d5];
    void *unk_800;
};
struct UnkStruct_0220fd04_3 {
    Vec d, v, v2, v3;
};

void func_ov003_0220fd04(struct UnkStruct_0220fd04_4 *o, struct UnkStruct_0220fd04_2 *b)
{
    struct UnkStruct_0220fd04_3 t;
    int ang;
    int y, z;
    struct UnkStruct_0220fd04 *p = &b->s;
    z = p->z;
    y = p->y;
    t.v.x = b->s.x;
    t.v.y = y;
    t.v.z = z;
    t.d.x = t.v.x - o->unk_5C;
    t.d.z = t.v.z - o->unk_64;
    ang = func_020e8ed8(t.d.x, t.d.z);
    t.v2.x = t.v.x;
    t.v2.y = t.v.y;
    t.v2.z = t.v.z;
    func_ov003_0220fd90(o->unk_7D4, ang, &t.v2);
    func_020109a0(o, 0x65, 3, 0);
    t.v3.x = t.v.x;
    t.v3.y = t.v.y;
    t.v3.z = t.v.z;
    func_ov003_02220db4(o->unk_800, &t.v3);
    func_0200f268(o, 0x1c);
    func_0200f328(o, 0x7da);
    func_0200f27c(o, 9);
}
