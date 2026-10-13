/* func_ov071_02279004 @ 0x02279004, 0x1e bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

int func_ov071_02279004(int arg0, const unsigned char *p, int n)
{
    int count = 0;
    int i = count;
    while (i < n) {
        if (*p == 0) {
            count++;
        }
        p++;
        i++;
    }
    return count;
}
