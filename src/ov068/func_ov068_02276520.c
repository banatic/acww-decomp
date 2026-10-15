/* func_ov068_02276520 @ 0x02276520, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202e1dc(void *argument0);
extern int func_020984e8(void);
extern char *func_02099640(int argument0);
extern int func_0209bba0(char *p);
extern void func_0209bb90(char *p, int n);
extern int data_ov068_022788ec;

int func_ov068_02276520(void *argument0)
{
    char *p;

    if (func_0202e1dc(argument0) == 0) {
        return 0;
    }

    p = func_02099640((int) func_020984e8()) + 0xa4;

    if (func_0209bba0(p + 0x10) == 1) {
        p += 0x10;
        func_0209bb90(p, 2);
    }

    data_ov068_022788ec = 0;
    return 1;
}
