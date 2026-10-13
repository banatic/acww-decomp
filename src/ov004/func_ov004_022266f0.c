/* func_ov004_022266f0 @ 0x022266f0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_022266f0;

extern void func_ov004_02226808(void *p, UnkStruct_022266f0 *v, int *w);
extern int func_ov004_0222683c(void *self, UnkStruct_022266f0 *v, int k, int arg);

void func_ov004_022266f0(void *self, int arg)
{
    UnkStruct_022266f0 v;
    func_ov004_02226808((char *) self + 0x8f0, &v, &v.c);
    func_ov004_0222683c(self, &v, 6, arg);
}
