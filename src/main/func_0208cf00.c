/* func_0208cf00 @ 0x0208cf00, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);
extern int func_0208a160(void *);
extern void func_0208cc64(void *);
extern void func_0208d014(void *);

void func_0208cf00(void *param)
{
    void *ptr;
    int result;

    ptr = (void *) ((char *) param + 0xc);
    func_0208a0c8(ptr);
    ptr = (void *) ((char *) param + 0xc);
    result = func_0208a160(ptr);
    if (result != 0) {
        func_0208cc64(param);
        func_0208d014(param);
    }
}
