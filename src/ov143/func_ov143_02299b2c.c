/* func_ov143_02299b2c @ 0x02299b2c, 0x44 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206ea10(int a);
extern void func_ov002_02208098(void *a, int b);
extern void func_ov143_02299640(void *a, int b);
extern void func_ov143_02299ba0(void *a, int b);
extern void func_ov143_0229a014(void *a);

void func_ov143_02299b2c(void *s)
{
    func_0206ea10(0x190);
    *(signed short *) ((char *) s + 0x9a) = -1;
    func_ov002_02208098(s, 0xa);
    func_ov143_02299640(s, 2);
    func_ov143_02299640(s, 8);
    func_ov143_02299ba0(s, 4);
    func_ov143_0229a014(s);
}
