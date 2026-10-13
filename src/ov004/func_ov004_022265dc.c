/* func_ov004_022265dc @ 0x022265dc, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_022265dc;
typedef struct {
    int x, y, z;
} UnkStruct_022265dc_2;

extern void func_0200e92c(UnkStruct_022265dc *t);
extern void func_0200e90c(UnkStruct_022265dc *t, int x, int y, int z);
extern void func_ov004_0222661c(void *p, UnkStruct_022265dc_2 v);
extern int func_0200e894(void *self, UnkStruct_022265dc *t);
extern void func_0200e91c(UnkStruct_022265dc *t);

int func_ov004_022265dc(void *self, UnkStruct_022265dc_2 *v, int c, int d)
{
    UnkStruct_022265dc t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x8d, c, d);
    func_ov004_0222661c(t.b, *v);
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}
