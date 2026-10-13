/* func_0207fd44 @ 0x0207fd44, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207fd44(int unused, unsigned short *ptr)
{
    int flag = 0;
    unsigned short val = *ptr;
    if (val >= 0x450c && val <= 0x45db) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
