/* func_ov068_0226e7e4 @ 0x0226e7e4, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_0203b144(void);
extern void func_02035684(int a, int b, int c);
extern void func_02035638(int a);
extern void func_ov068_0226e878(void *ptr, int b);

int func_ov068_0226e7e4(void *arg)
{
    if (func_02014868((char *) arg + 0x618) != 0) {
        goto done;
    }
    func_0203b144();
    func_02035684(0x13, 0x3c, 0);
    func_02035638(0x47);
    func_ov068_0226e878(arg, 3);
done:
    return 1;
}
