/* func_ov111_0229f3ac @ 0x0229f3ac, 0x84 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];

extern int func_ov095_02299a00(void *ptr);
extern int func_ov095_0229c448(void *ptr, int a, int b);
extern int func_ov111_0229f660(void *ptr);
extern void func_ov002_0220a1dc(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov095_0229c8e4(void *ptr, int a);
extern void func_ov111_0229f0ec(void *ptr);

int func_ov111_0229f3ac(void *arg)
{
    int a;
    if (data_021fbe40[1] & 1) {
        goto body;
    }
    return 0;
body:
    a = func_ov095_02299a00((char *) arg + 0xac);
    if (a == -1) {
        return 0;
    }
    if (func_ov095_0229c448((char *) arg + 0xac, a, 9) == 0x106) {
        if (func_ov111_0229f660(arg) != 0) {
            func_ov002_0220a1dc((char *) arg + 0x3d38);
            func_ov002_02208098((void *) (arg), 13);
            return 1;
        } else {
            return 0;
        }
    } else {
        func_ov095_0229c8e4((char *) arg + 0xac, a);
        func_ov111_0229f0ec(arg);
        return 1;
    }
}
