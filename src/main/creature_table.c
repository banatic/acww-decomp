/* creature_table: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204fb08 @ 0x0204fb08, 0x34 bytes, Thumb
 * func_0204fafc @ 0x0204fafc, 0xc bytes, Thumb
 * func_0204fa8c @ 0x0204fa8c, 0x70 bytes, Thumb
 * func_0204fa68 @ 0x0204fa68, 0x24 bytes, Thumb
 */

extern void func_0209df94(unsigned char *);

int func_0204fb08(unsigned int r0)
{
    int r1 = 0;
    if ((r0 >= 4 && r0 < 9) || (r0 >= 16 && r0 < 21)) {
        r1 = 0;
    } else if (r0 >= 9 && r0 < 16) {
        r1 = 1;
    } else if ((r0 >= 21 && r0 <= 24) || (r0 < 4)) {
        r1 = 2;
    }
    return r1;
}

int func_0204fafc(unsigned int x)
{
    return x > 15;
}

unsigned char func_0204fa8c(unsigned char v)
{
    unsigned char local[4];

    if (v >= 1 && v <= 7) {
        return v;
    }
    if (v == 8) {
        func_0209df94(local);
        if (func_0204fafc((unsigned char) local[0]) != 0) {
            v = (unsigned char) (v + 1);
        }
        return v;
    }
    if (v == 9) {
        func_0209df94(local + 2);
        if (func_0204fafc((unsigned char) local[2]) == 0) {
            return (unsigned char) (v + 1);
        }
        return (unsigned char) (v + 2);
    }
    if (v >= 10 && v <= 12) {
        return (unsigned char) (v + 2);
    }
    return 1;
}

int func_0204fa68(int r0)
{
    if (r0 < 0 || r0 >= 0x38) {
        return 0;
    }
    if (r0 >= 0x23) {
        return 3;
    }
    if (r0 >= 9 && r0 <= 0xb) {
        return 2;
    }
    return 1;
}
