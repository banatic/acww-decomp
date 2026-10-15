/* func_020aaa20 @ 0x020aaa20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7f0c(void);

int func_020aaa20(void *object)
{
    int result;

    if (func_020a7f0c() == 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
