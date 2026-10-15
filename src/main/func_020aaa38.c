/* func_020aaa38 @ 0x020aaa38, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a8028(int a, int b);

int func_020aaa38(void *object)
{
    int result;
    int ret;

    result = func_020a8028(0, 0);
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}
