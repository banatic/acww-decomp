/* func_020b48ec @ 0x020b48ec, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b48ec(char *out, int arg1, int num, int digits);

void func_020b48ec(char *out, int arg1, int num, int digits)
{
    int i;
    int limit;

    if (num == 0) {
        out[0] = 0;
        out[1] = '0';
    } else {
        i = 1;
        limit = digits * 2;
        while (i < limit && num != 0) {
            int q = num / 10;
            out[i] = (char) (0x30 + (num - q * 10));
            num = q;
            i += 2;
        }
    }
}
