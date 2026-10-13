/* func_02079468 @ 0x02079468, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02079468(unsigned char *ptr)
{
    int tmp;
    tmp = ptr[0x1e] * 2;
    if (tmp > 0x20) {
        tmp = 0x20;
    }
    ptr[0x1e] = tmp;
}
