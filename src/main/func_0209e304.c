/* func_0209e304 @ 0x0209e304, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e304(unsigned char *r0, int r1);

void func_0209e304(unsigned char *r0, int r1)
{
    unsigned char r2;
    int r1_local;

    r2 = r0[5];
    r1_local = r2 + r1;
    if (r1_local > 0x63) {
        r1_local -= 0x64;
    }
    r0[5] = (unsigned char) r1_local;
}
