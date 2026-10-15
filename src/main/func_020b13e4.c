/* func_020b13e4 @ 0x020b13e4, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020b15b0(void);
extern void func_02051bf8(void *, int);
extern int func_020b1974(void *, int);
extern void func_02051c08(void *, const void *, int);

void func_020b13e4(void *arg0, int arg1)
{
    char *base;
    int result;
    base = (char *) func_020b15b0();
    func_02051bf8(arg0, 6);
    result = func_020b1974((void *) base, arg1);
    if (result != 0) {
        func_02051c08(base + arg1 * 74 + 30, arg0, 6);
    }
    return;
}
