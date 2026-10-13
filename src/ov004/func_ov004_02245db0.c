/* func_ov004_02245db0 @ 0x02245db0, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203e328(void);
extern void func_0208e2a4(void *a);
extern int func_0206f78c(void);
extern void func_0206f74c(void);
extern void func_0209e474(void *a);
extern int func_0209e3ac(void *a, void *b, int c);
extern void func_0206f774(void);
extern void func_0206f780(void);

int func_ov004_02245db0(void *self)
{
    unsigned char i;
    int b[2];
    char *p;

    func_0203e328();
    i = 0;
    p = (char *) self + 0x9c;
    do {
        func_0208e2a4(p + (i << 7));
        i++;
    } while (i < 5);
    if (func_0206f78c() != 0) {
        func_0206f74c();
        b[0] = 0;
        b[1] = 0;
        func_0209e474(b);
        if (func_0209e3ac((char *) self + 0x328, b, 0x3f) == -1) {
            func_0206f774();
        } else {
            func_0206f780();
        }
    }
    return 1;
}
