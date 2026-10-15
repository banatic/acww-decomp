/* func_0207e738 @ 0x0207e738, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099728(unsigned int);

int func_0207e738(unsigned int object)
{
    int r3;
    int r2;
    unsigned short r1;
    int r0;

    r0 = func_02099728(object);
    r3 = 1;
    r2 = 0;
    r1 = *(unsigned short *) r0;
    if (r1 >= 0x1380 && r1 <= 0x139f) {
        r2 = r3;
    }
    if (r2 == 0) {
        if (r1 < 0x13a0 || r1 > 0x13a7) {
            r3 = 0;
        }
    }
    return r3;
}
