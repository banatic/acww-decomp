/* func_ov004_0222920c @ 0x0222920c, 0x4a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char a[0xc];
    char b[0x14];
} UnkStruct_0222920c;

extern void func_0200e92c(UnkStruct_0222920c *t);
extern void func_0200e90c(UnkStruct_0222920c *t, int x, int y, int z);
extern void func_ov004_022292c0(void *p, int a, int b, int c);
extern int func_0200e894(void *self, UnkStruct_0222920c *t);
extern void func_0200e91c(UnkStruct_0222920c *t);

int func_ov004_0222920c(void *self, int *b, int *c, short *d, int e, short g)
{
    UnkStruct_0222920c t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x26, e, g);
    func_ov004_022292c0(t.b, *b, *c, *d);
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}
