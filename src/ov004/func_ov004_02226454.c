/* func_ov004_02226454 @ 0x02226454, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char a[0xc];
    char b[0x10];
} UnkStruct_02226454;
typedef struct {
    int x, y, z;
} UnkStruct_02226454_2;

extern unsigned int func_0200e92c(UnkStruct_02226454 *t);
extern void func_0200e90c(UnkStruct_02226454 *t, int x, int y, int z);
extern void func_ov004_02226494(void *p, UnkStruct_02226454_2 v);
extern int func_0200e894(void *self, UnkStruct_02226454 *t);
extern int func_0200e91c(UnkStruct_02226454 *t);

int func_ov004_02226454(void *self, UnkStruct_02226454_2 *v, int c, int d)
{
    UnkStruct_02226454 t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x8e, c, d);
    func_ov004_02226494(t.b, *v);
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}
