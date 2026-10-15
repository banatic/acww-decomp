/* func_ov126_0229ff68 @ 0x0229ff68, 0x74 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_0229f7c8(void *p, int a);
extern void func_ov002_0220a000(void *p, int a, int b, int c, int d);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov126_0229ff68(void *param)
{
    if (func_ov126_0229f7c8(param, 0x80)) {
        func_ov002_0220a000((char *) param + 0x3f90, *(int *) ((char *) param + 0x98), 0x28, 3, 2);
        *(char *) ((char *) param + 0xae) = 6;
    } else {
        int a, b;
        a = func_ov095_02299b7c((char *) param + 0x19c);
        b = func_ov095_02299b38((char *) param + 0x19c);
        func_ov002_0220a000((char *) param + 0x3f90, a, b, 3, 2);
        *(char *) ((char *) param + 0xae) = 4;
    }
    func_ov002_02208098((void *) (param), 8);
}
