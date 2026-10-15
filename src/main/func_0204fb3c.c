/* func_0204fb3c @ 0x0204fb3c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df94(void *);
extern void func_0209def4(void *);
extern unsigned char func_0204fa8c(unsigned char);
extern unsigned char func_0204fb08(unsigned char);
extern int func_0204fb80(int, int, int, int, int);

int func_0204fb3c(int r0, int r1, int r2)
{
    unsigned char local[4];
    unsigned char a, b;
    int c;

    func_0209df94(local);
    a = local[1];
    func_0209def4(local + 2);
    b = local[3];
    c = func_0204fa8c(a);
    return func_0204fb80(r0, r1, r2, c, func_0204fb08(b));
}
