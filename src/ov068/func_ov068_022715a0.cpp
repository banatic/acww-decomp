/* func_ov068_022715a0 @ 0x022715a0, 0xa4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct Vec {
    int x, y, z;
};
struct UnkStruct_022715a0 {
    char pad_00[0x204];
    char unk_204[0x238 - 0x204];
    short unk_238;
    short unk_23A;
    char pad_23C[0x251 - 0x23c];
    signed char unk_251;
};

extern "C" int func_ov068_02271494(struct UnkStruct_022715a0 *, struct Vec *);
extern "C" void func_ov003_0222d518(struct UnkStruct_022715a0 *, int);
extern "C" void func_020eaca0(struct Vec *, void *, struct Vec *);
extern "C" void func_ov003_022321b8(struct Vec *, struct Vec *, int);
extern "C" void VEC_Subtract(void *, struct Vec *, void *);

extern "C" int func_ov068_022715a0(struct UnkStruct_022715a0 *a, short *b, struct Vec *c)
{
    struct Vec v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    void *m = a->unk_204;
    int n = func_ov068_02271494(a, &v);
    if (n == 0) {
        a->unk_23A = (short) 0xffff8000;
        a->unk_238 = 1;
        a->unk_251 = 0;
        func_ov003_0222d518(a, 0x1000);
    } else if (n > 0 && n < 5) {
        struct Vec r;
        func_020eaca0(&r, m, &v);
        c->x = r.x;
        c->y = r.y;
        c->z = r.z;
        c->y = 0;
        func_ov003_022321b8(c, c, 2);
        VEC_Subtract(m, c, m);
        return 1;
    } else {
        a->unk_251 = 9;
        *b = 0;
    }
    return 0;
}