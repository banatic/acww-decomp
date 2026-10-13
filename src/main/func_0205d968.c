/* func_0205d968 @ 0x0205d968, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_0205d968(char *base, int x, int y)
{
    char *p = base + y * 18;
    p += x * 2;
    p += 72;
    return *(unsigned short *) p;
}
