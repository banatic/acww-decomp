/* func_ov004_02226c2c @ 0x02226c2c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_02226c2c;
typedef struct {
    int x, y, z;
} UnkStruct_02226c2c_2;

extern unsigned int func_0200e92c(UnkStruct_02226c2c *t);
extern void func_0200e90c(UnkStruct_02226c2c *t, int x, int y, int z);
extern void func_ov004_02226c6c(void *p, UnkStruct_02226c2c_2 v);
extern int func_0200e894(void *self, UnkStruct_02226c2c *t);
extern int func_0200e91c(UnkStruct_02226c2c *t);

int func_ov004_02226c2c(void *self, UnkStruct_02226c2c_2 *v, int c, int d)
{
    UnkStruct_02226c2c t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x8b, c, d);
    func_ov004_02226c6c(t.b, *v);
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}
