/* func_ov126_022a01dc @ 0x022a01dc, 0x44 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_022a0740(void *a);
extern void func_ov126_022a06d8(void *a);
extern void func_ov095_0229b3ec(void *p);
extern int func_ov126_022a0220(void *a, void *b);
extern void func_ov126_022a0168(void *a);
extern void func_ov126_022a08c4(void *a);

int func_ov126_022a01dc(void *a, void *b)
{
    int ret;

    if (func_ov126_022a0740(a)) {
        func_ov126_022a06d8(a);
        func_ov095_0229b3ec((char *) a + 0x19c);
    }
    ret = func_ov126_022a0220(a, b);
    func_ov126_022a0168(a);
    func_ov126_022a08c4(a);
    return ret;
}
