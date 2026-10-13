/* func_ov003_0220fa5c @ 0x0220fa5c, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

struct Vec {
    int x, y, z;
};
struct UnkStruct_0220fa5c {
    int a, b;
    unsigned char c, d;
};
struct In {
    char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char unk_14, unk_15;
};
struct UnkStruct_0220fa5c_2 {
    char pad_00[0x5c];
    int unk_5C, unk_60, unk_64;
    char pad_68[0x7d4 - 0x68];
    char unk_7D4[0x8f0 - 0x7d4];
    char unk_8F0[4];
};

extern "C" int func_020e8ed8(int, int);
extern "C" void func_ov003_0220fb14(void *, int, int, int, int, int);
extern "C" void func_ov003_0220fafc(void *, int, int, int);
extern "C" void func_020109a0(struct UnkStruct_0220fa5c_2 *, int, int, int);
extern "C" void func_020109fc(struct UnkStruct_0220fa5c_2 *, int, int, int);
extern "C" void func_0200f27c(struct UnkStruct_0220fa5c_2 *, int);

extern "C" void func_ov003_0220fa5c(struct UnkStruct_0220fa5c_2 *o, struct In *p)
{
    volatile struct Vec d;
    volatile struct Vec b;
    struct UnkStruct_0220fa5c *q = (struct UnkStruct_0220fa5c *) &p->unk_0C;
    int u = q->c;
    int v = q->d;
    int z = q->b;
    int by = o->unk_60;
    int bx = p->unk_0C;
    b.x = bx;
    b.y = by;
    b.z = z;
    int dx = bx - o->unk_5C;
    d.x = dx;
    int dz = z - o->unk_64;
    d.z = dz;
    int ang = func_020e8ed8(dx, dz);
    func_ov003_0220fb14(o->unk_7D4, ang, b.x, b.z, u, v);
    func_ov003_0220fafc(o->unk_8F0, b.x, b.z, (unsigned char) (u | (v << 4)));
    if (v) {
        func_020109a0(o, 0x66, 3, 0);
    } else {
        func_020109fc(o, 0x66, 3, 0);
    }
    func_0200f27c(o, 9);
}