/* func_02057730 @ 0x02057730, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int strlen(const char *);

void func_02057730(char *dst, const char *src)
{
    if (src) {
        unsigned int n = strlen(src) + 1;
        unsigned int i;
        for (i = 0; i < 17; i++) {
            if (i < n) {
                dst[i] = src[i];
            } else {
                dst[i] = 0;
            }
        }
    }
}
