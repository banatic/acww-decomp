/* func_ov003_0220e860 @ 0x0220e860, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(void *, int, int);
extern void func_020109fc(void *, int, int, int);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);
extern void func_ov003_0220e8ec(void *, unsigned char, unsigned char);
extern void func_0200f328(void *, int);
typedef struct {
    int x, y, z;
} Vec;
struct UnkStruct_0220e860 {
    char pad_00[0xc];
    unsigned char c0;
    unsigned char c1;
};
struct UnkStruct_0220e860_2 {
    char pad_00[0x5a0];
    char sub5a0[1];
    char pad_5A1[0x7d4 - 0x5a1];
    int unk_7D4;
    int unk_7D8;
    int unk_7DC;
    char pad_7E0[0x8f0 - 0x7e0];
    char sub8f0[1];
};
void func_ov003_0220e860(struct UnkStruct_0220e860_2 *o, struct UnkStruct_0220e860 *b)
{
    Vec v;
    unsigned char *p = &b->c0;
    int *q = &o->unk_7D4;
    int x = *p;
    int z = *(p + 1);

    func_0204f794(&v, x, z);
    o->unk_7D4 = v.x;
    q[1] = v.z;
    q[2] = -1;
    func_020109fc(o, 0x90, 3, 0);
    if (func_0200fbe0(o) == 4) {
        func_0205eae0(o->sub5a0, 0xf, 3, 0);
    }
    func_ov003_0220e8ec(o->sub8f0, (unsigned char) x, (unsigned char) z);
    func_0200f328(o, 0x7ee);
}
