/* func_02080b98 @ 0x02080b98, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(void *ptr);

int func_02080b98(void *param1, int param2)
{
    int i;
    void *p;
    int result;

    i = 0;
    p = param1;
    while (i < param2) {
        if (func_02003704((char *) p + 0x7a0) == 0) {
            return i;
        }
        p = (char *) p + 0x7ec;
        i++;
    }
    return -1;
}
