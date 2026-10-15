/* func_ov003_02215394 @ 0x02215394, 0x52 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *p);
extern int func_0200f554(void *p);
extern int func_0201100c(void *p);
extern void func_02010d64(void *p);
extern int func_020113a4(int a, int b, int c);
extern void func_0201107c(void *p, int *q);
extern void func_ov003_022153e8(void *p);

void func_ov003_02215394(void *arg)
{
    int val, local;
    char *p;

    func_02010f5c(arg);
    if (func_0200f554(arg) != 0) {
        func_0201100c(arg);
    }
    func_02010d64(arg);

    p = (char *) arg;
    p += 0x98;
    val = *(int *) p;

    if (val < 0) {
        val = -val;
    }

    local = -1 * func_020113a4(val, 0, 0xc5);

    func_0201107c(arg, &local);
    func_ov003_022153e8(arg);
}
