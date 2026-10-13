/* func_0203fa84 @ 0x0203fa84, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203fa84(unsigned char *r0);

void func_0203fa84(unsigned char *r0)
{
    int r2;
    unsigned char r1;

    r2 = 0;
    r1 = 0xff;
    do {
        r0[r2] = r1;
        r2++;
    } while (r2 < 4);
}
