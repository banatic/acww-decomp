/* func_020b3f44 @ 0x020b3f44, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b3f44(char *p)
{
    int offset = 0;
    int i = 0;
    while (p[offset] == 'M') {
        p += 4;
        i++;
    }
    return i;
}
