/* func_ov126_022a0c34 @ 0x022a0c34, 0x30 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229bf48(void *p);
extern int func_ov002_0220b8ac(void *p, int flag);
extern void func_ov126_022a0be0(void *p);

void func_ov126_022a0c34(void *p)
{
    func_ov095_0229bf48((char *) p + 0x19c);
    if (func_ov002_0220b8ac((char *) p + 0x412c, 1)) {
        func_ov126_022a0be0(p);
    }
}
