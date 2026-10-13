/* func_0209d970 @ 0x0209d970, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d970(unsigned char *r0, int r1);

void func_0209d970(unsigned char *r0, int r1)
{
    unsigned char r4;
    int r3;
    int r2;

    r4 = *r0;
    r3 = 1;
    r2 = 3;
    r1 &= r2;
    r3 <<= r1;
    r4 &= ~r3;
    *r0 = r4;
}
