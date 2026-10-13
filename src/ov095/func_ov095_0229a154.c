/* func_ov095_0229a154 @ 0x0229a154, 0x1a bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov090_02298f84(int a);
extern void func_ov095_0229aa74(void *a);

void func_ov095_0229a154(void *a, int b)
{
    int c;
    c = func_ov090_02298f84(b);
    c += 0xfb;
    *(int *) ((char *) a + 0x28) = c;
    func_ov095_0229aa74(a);
}
