/* func_0207fd94 @ 0x0207fd94, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207fd94(int unused, unsigned short *p)
{
    int found;
    unsigned short val;

    found = 0;
    val = *p;
    if (val >= 0x12b0 && val <= 0x12e7) {
        found = 1;
    }
    if (found) {
        return 1;
    } else {
        return 0;
    }
}
