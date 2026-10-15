/* func_020a7c74 @ 0x020a7c74, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7c38(void *a);
extern int func_020a7c98(void *a, int n);

int func_020a7c74(void *a, int b)
{
    int n;
    int result;

    n = func_020a7c38(a) - b - 1;
    result = 0;
    if (n >= 0) {
        result = func_020a7c98(a, n);
    }
    return result;
}
