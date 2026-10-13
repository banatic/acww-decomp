/* func_ov098_022a28ac @ 0x022a28ac, 0x24 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f0dc(void *a, unsigned char b);
extern int func_ov003_02219750(int v);
extern void func_ov002_02208098(void *a, int v);

void func_ov098_022a28ac(void *a)
{
    if (func_ov003_02219750(func_ov096_0229f0dc(a, *(unsigned char *) ((char *) a + 0xb6))) != 0) {
        func_ov002_02208098(a, 0x36);
    }
}
