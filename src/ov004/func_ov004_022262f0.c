/* func_ov004_022262f0 @ 0x022262f0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_022262f0;

extern void func_ov004_0222642c(void *p, UnkStruct_022262f0 *v, int *w);
extern int func_ov004_02226454(void *self, UnkStruct_022262f0 *v, int k, int arg);

void func_ov004_022262f0(void *self, int arg)
{
    UnkStruct_022262f0 v;
    func_ov004_0222642c((char *) self + 0x8f0, &v, &v.c);
    func_ov004_02226454(self, &v, 6, arg);
}
