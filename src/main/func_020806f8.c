/* func_020806f8 @ 0x020806f8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081edc(void *object);
extern int func_02081d20(char *);

int func_020806f8(char *p)
{
    int max = -128;
    int i = 0;
    do {
        if (func_02081edc(p)) {
            int ret = func_02081d20(p);
            if (ret > max) {
                max = ret;
            }
        }
        p += 0x80;
        i++;
    } while (i < 8);
    return max;
}
