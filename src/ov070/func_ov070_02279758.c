/* func_ov070_02279758 @ 0x02279758, 0x1e bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

int func_ov070_02279758(int unused, const unsigned char *s, int n)
{
    int count = 0;
    int i = 0;
    while (i < n) {
        if (*s == 0) {
            count++;
        }
        s++;
        i++;
    }
    return count;
}
