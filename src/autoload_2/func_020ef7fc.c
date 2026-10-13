/* func_020ef7fc @ 0x020ef7fc, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

int func_020ef7fc(unsigned char *self)
{
    int i;
    int n;

    n = (int) self[0x36];
    i = 0;
    if (n > 0) {
        do {
            if (*(int *) (self + 8) == 0 && (self[0x11] & 2) == 0) {
                return i;
            }
            i = i + 1;
            self = self + 0xc;
        } while (i < n);
    }
    return n;
}
