/* func_0207e6d4 @ 0x0207e6d4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02099710(void);

int func_0207e6d4(void)
{
    unsigned short *p = func_02099710();
    int flag = (*p >= 0x12a8 && *p <= 0x12af);
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
