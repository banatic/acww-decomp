/* func_0205d950 @ 0x0205d950, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0205d950(unsigned char *p, int i, int j, int v)
{
    unsigned char *q = p + j * 0x12;
    q = q + i * 2;
    *(short *) (q + 0x48) = (short) v;
}