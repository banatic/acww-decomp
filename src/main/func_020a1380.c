/* func_020a1380 @ 0x020a1380, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a132c(void);

int func_020a1380(void)
{
    int result;
    int value;

    if (func_020a132c() != 0) {
        value = func_020a132c();
        result = *(unsigned char *) (value + 0xd6);
    } else {
        result = 0;
    }
    return result;
}
