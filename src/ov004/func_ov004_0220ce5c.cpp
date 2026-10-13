/* func_ov004_0220ce5c @ 0x0220ce5c, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct Vec {
    int x, y, z;
};

extern "C" void func_020ea6e0(struct Vec *, short);
extern "C" int func_ov004_0220ebd4(void *, struct Vec *);
extern "C" void func_01ffd070(struct Vec *, void *, struct Vec *);
extern "C" void func_ov004_0220ccf8(void *, int);
extern "C" int func_ov004_0220ec8c(void *);
extern "C" void func_02095380(int);

struct UnkStruct_0220ce5c {
    char pad_00[0xc];
    unsigned short unk_0C;
    char pad_0E[0x5c - 0xe];
    char unk_5C[0x16c - 0x5c];
    unsigned short unk_16C;
    char pad_16E[2];
    int unk_170, unk_174, unk_178;
};

extern "C" int func_ov004_0220ce5c(struct UnkStruct_0220ce5c *o, unsigned short a)
{
    struct Vec v;
    v.x = 0;
    v.y = 0;
    v.z = 0x2000;
    func_020ea6e0(&v, (short) (a + 0x8000));
    if (func_ov004_0220ebd4(o, &v)) {
        struct Vec r;
        func_01ffd070(&r, o->unk_5C, &v);
        o->unk_170 = r.x;
        o->unk_174 = r.y;
        o->unk_178 = r.z;
        o->unk_16C = a;
        func_ov004_0220ccf8(o, 4);
        int b = (o->unk_0C == 0x3d);
        if (!b) {
            int id = func_ov004_0220ec8c(o);
            if (id != 0xffff) {
                func_02095380(id);
            }
        }
        return 1;
    }
    return 0;
}