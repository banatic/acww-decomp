/* func_0201131c @ 0x0201131c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(int value);
extern unsigned short *func_02099710(int value);

void func_0201131c(unsigned short *dest, int arg2)
{
    int tmp;
    tmp = func_02011368(arg2);
    *dest = 0xfff1;
    if (tmp != 0) {
        *dest = *func_02099710(tmp);
    }
}
