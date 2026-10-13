/* func_020bec60 @ 0x020bec60, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020bec60(char *p, int off, char val)
{
    if (off >= 0 && val >= 0) {
        p += off - 12;
        p[4] = val;
    }
}
