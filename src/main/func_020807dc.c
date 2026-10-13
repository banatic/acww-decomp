/* func_020807dc @ 0x020807dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d28(void *src, void *dst);

int func_020807dc(void *param0, void *param1)
{
    int i;
    int result;

    i = 0;
    while (i < 8) {
        if (func_02081d28((char *) param0 + (i << 7), param1)) {
            return i;
        }
        i++;
    }
    return -1;
}
