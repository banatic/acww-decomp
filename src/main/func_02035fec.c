/* func_02035fec @ 0x02035fec, 0x8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02035fec(char *p, int v)
{
    p[4] = 1;
    *(short *) (p + 6) = (short) v;
}
