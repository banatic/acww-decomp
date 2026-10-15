/* func_ov003_02218844 @ 0x02218844, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02218844 {
    int a;
    int b;
    short c;
};
struct Other {
    char pad_00[0xc];
    struct UnkStruct_02218844 sub;
};

extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern void func_ov003_022188c8(void *dst, int, int, int);
extern void func_ov003_022188ac(void *dst, int, int, int);

void func_ov003_02218844(char *self, struct Other *other, int previous)
{
    struct UnkStruct_02218844 *sub = &other->sub;
    int a, b;
    short c;

    func_020109a0(self, 0x37, 3, 0);
    a = sub->a;
    b = sub->b;
    c = sub->c;
    func_ov003_022188c8(self + 0x7d4, a, b, c);
    func_ov003_022188ac(self + 0x8f0, a, b, c);
}
