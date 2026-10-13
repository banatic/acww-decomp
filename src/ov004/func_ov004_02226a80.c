/* func_ov004_02226a80 @ 0x02226a80, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_02226a80;

extern void func_ov004_02226bf8(void *p, UnkStruct_02226a80 *v, int *w);
extern int func_ov004_02226c2c(void *self, UnkStruct_02226a80 *v, int k, int arg);

void func_ov004_02226a80(void *self, int arg)
{
    UnkStruct_02226a80 v;
    func_ov004_02226bf8((char *) self + 0x8f0, &v, &v.c);
    func_ov004_02226c2c(self, &v, 6, arg);
}
