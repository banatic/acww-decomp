/* func_0208e4c0 @ 0x0208e4c0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e508(void *, int);
extern void *func_0208a1c8(void *);
extern void func_0208a1e0(void *, int, int);

void func_0208e4c0(void *arg, int argument1)
{
    void *ret;
    void *ret2;

    func_0208e508(arg, (int) argument1);
    ret = func_0208a1c8((char *) arg + 0xc);
    func_0208a1e0((char *) arg + 0xc, ((int *) ret)[1] - 1, 0);
    if (*((unsigned char *) arg + 0x49) != 0) {
        ret2 = func_0208a1c8((char *) arg + 0x2c);
        func_0208a1e0((char *) arg + 0x2c, ((int *) ret2)[1] - 1, 0);
    }
}
