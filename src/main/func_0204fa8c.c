/* func_0204fa8c @ 0x0204fa8c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df94(unsigned char *);
extern int func_0204fafc(unsigned char);

unsigned char func_0204fa8c(unsigned char v)
{
    unsigned char local[4];

    if (v >= 1 && v <= 7) {
        return v;
    }
    if (v == 8) {
        func_0209df94(local);
        if (func_0204fafc(local[0]) != 0) {
            v = (unsigned char) (v + 1);
        }
        return v;
    }
    if (v == 9) {
        func_0209df94(local + 2);
        if (func_0204fafc(local[2]) == 0) {
            return (unsigned char) (v + 1);
        }
        return (unsigned char) (v + 2);
    }
    if (v >= 10 && v <= 12) {
        return (unsigned char) (v + 2);
    }
    return 1;
}
