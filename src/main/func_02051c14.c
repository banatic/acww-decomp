/* func_02051c14 @ 0x02051c14, 0x76 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051ce0(const unsigned short *a, int b, int e, int *d);
extern int func_02051d30(unsigned short value);

int func_02051c14(const unsigned short *a, int b, int c, int *d, int e)
{
    int i;
    int sum = 0;
    int count = func_02051ce0(a, b, e, d);

    for (i = 0; i < count; i++) {
        sum += func_02051d30(a[i]);
        if (sum > c) {
            *d = i;
            return 1;
        }
    }
    *d = count;
    if (count == b) {
        return a[count - 1] == 10 ? 3 : 2;
    }
    if (count == 0) {
        return 0;
    }
    return a[count - 1] == 10 ? 3 : 0;
}
