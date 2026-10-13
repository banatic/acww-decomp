/* func_02042a08 @ 0x02042a08, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02042a08(int unused, volatile unsigned char *dst, const unsigned char *src, int count)
{
    int i;
    int zeros = 0;
    int cur = *src;

    for (i = 0; i < count; ++i) {
        *dst = (cur >> (i & 7)) & 1;
        if (*dst == 0) {
            ++zeros;
        }
        if ((i + 1) % 8 == 0) {
            ++src;
            cur = *src;
        }
        ++dst;
    }

    return zeros;
}
