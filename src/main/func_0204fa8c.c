/* func_0204fa8c @ 0x0204fa8c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df94(unsigned char *);
extern int func_0204fafc(unsigned char);

unsigned char func_0204fa8c(unsigned char r0)
{
    unsigned char r4;
    unsigned char local[4];
    unsigned char r0_2;

    r4 = r0;
    if (r4 >= 1 && r4 <= 7) {
        goto label_0204faf4;
    }
    if (r4 == 8) {
        func_0209df94(local);
        if (func_0204fafc(local[0]) != 0) {
            r4 = (unsigned char) (r4 + 1);
        }
        r0_2 = r4;
        goto label_0204faf4;
    }
    if (r4 == 9) {
        func_0209df94(local + 2);
        if (func_0204fafc(local[2]) == 0) {
            r0_2 = (unsigned char) (r4 + 1);
            goto label_0204faf4;
        }
        r0_2 = (unsigned char) (r4 + 2);
        goto label_0204faf4;
    }
    if (r4 >= 10 && r4 <= 12) {
        r0_2 = (unsigned char) (r4 + 2);
        goto label_0204faf4;
    }
    r0_2 = 1;
label_0204faf4:
    return r0_2;
}
