/* func_020691a4 @ 0x020691a4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps both pair words loaded before the first compare; the plain condition compares a before loading b */

extern void func_020a8764(void *);
extern void func_02069168(void *);

void func_020691a4(void *self)
{
    int a, b;
    func_020a8764((char *) self + 0x2c);
    if (*(unsigned int *) ((char *) self + 0x28) == 0) {
        a = *(int *) ((char *) self + 0x2c);
        if ((self && self) && self) {
        }
        b = *(int *) ((char *) self + 0x30);
        if ((a == 0xa) && (b == 0)) {
            func_02069168(self);
        }
    }
}
