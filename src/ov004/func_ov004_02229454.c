/* func_ov004_02229454 @ 0x02229454, 0x4a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char a[0xc];
    char b[0x14];
} UnkStruct_02229454;

extern void func_0200e92c(UnkStruct_02229454 *t);
extern void func_0200e90c(UnkStruct_02229454 *t, int x, int y, int z);
extern void func_ov004_02229508(void *p, int a, int b, int c);
extern int func_0200e894(void *self, UnkStruct_02229454 *t);
extern void func_0200e91c(UnkStruct_02229454 *t);

int func_ov004_02229454(void *self, int *b, int *c, short *d, int e, short g)
{
    UnkStruct_02229454 t;
    int r;
    func_0200e92c(&t);
    func_0200e90c(&t, 0x25, e, g);
    func_ov004_02229508(t.b, *b, *c, *d);
    r = func_0200e894(self, &t);
    func_0200e91c(&t);
    return r;
}
