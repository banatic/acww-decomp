/* func_ov071_02278fd0 @ 0x02278fd0, 0x34 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov071_02279004(int a, unsigned char *p, int n);
extern int func_020644cc(int value);

int func_ov071_02278fd0(int a, unsigned char *p, int n)
{
    int r, result, m, i;

    r = func_ov071_02279004(a, p, n);
    result = 0;
    m = func_020644cc(r);

    for (i = result; i < n; i++) {
        if (*p == 0) {
            if (m == 0) {
                result = i;
                break;
            }
            m--;
        }
        p++;
    }

    return result;
}
