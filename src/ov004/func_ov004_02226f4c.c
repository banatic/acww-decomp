/* func_ov004_02226f4c @ 0x02226f4c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02226f4c {
    int a;
    int b;
    int c;
};
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200fa8c(struct UnkStruct_02226f4c *v, void *self);
extern void func_ov004_02226f90(void *dst, struct UnkStruct_02226f4c v);
extern void func_ov004_022318f8(void);
extern void func_ov004_02230d30(void);
void func_ov004_02226f4c(unsigned char *self)
{
    struct UnkStruct_02226f4c v;
    func_020109a0(self, 0x78, 3, 0);
    func_0200fa8c(&v, self);
    v.c = v.c + 0x2000;
    func_ov004_02226f90(self + 0x7d4, v);
    func_ov004_022318f8();
    func_ov004_02230d30();
}
