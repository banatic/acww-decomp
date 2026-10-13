/* func_ov052_02261158 @ 0x02261158, 0x34 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov052_0226118c(int a, const unsigned char *arr, int n);
extern int func_020644cc(int value);

int func_ov052_02261158(int a, const unsigned char *arr, int n)
{
    const unsigned char *p;
    int tmp;
    int result;
    int pos;
    int i;

    p = arr;
    tmp = func_ov052_0226118c(a, arr, n);
    result = 0;
    pos = func_020644cc(tmp);
    i = 0;

    while (i < n) {
        if (*p == 0) {
            if (pos == 0) {
                result = i;
                break;
            }
            pos--;
        }
        p++;
        i++;
    }

    return result;
}
