/* func_020ed79c @ 0x020ed79c, 0x98 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020ed874(void *a, void *b, unsigned short index, void *c);

int func_020ed79c(void *a, void *b, unsigned int mask, void *c)
{
    unsigned int i;

    if (a != 0 && b != 0 && mask != 0) {
        for (i = 0; i < 16; i++) {
            if (mask & (1 << i)) {
                if (func_020ed874(a, b, (unsigned short) i, c) == 0) {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}
