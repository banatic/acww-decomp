/* func_0204c438 @ 0x0204c438, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204b3cc(void *dst, int val);
extern void func_02061e2c(void *p, void *q);
extern int func_0204bd08(void *p);
extern int func_0204bcdc(void *p);
extern int func_0204c358(void *p);
extern int func_0204c3c8(void *p);
extern void func_0204c4b8(void *dst, void *src);
extern void func_020051b0(void *p);

int func_0204c438(void *p0, void *p1)
{
    char local[8];
    int result;

    func_0204b3cc(local, 0x0000fff1);
    result = 0;
    func_02061e2c(local + 2, p0);
    if (func_0204bd08(local + 2) || func_0204bcdc(local + 2)) {
        if (func_0204c358(local + 2) == 0 && func_0204c3c8(local + 2) == 0) {
            func_0204c4b8(local, local + 2);
            result = 1;
        }
    }
    if (p1) {
        func_0204c4b8(p1, local);
    }
    func_020051b0(local + 2);
    func_020051b0(local);
    return result;
}
