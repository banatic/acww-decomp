/* network_20: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ed79c @ 0x020ed79c, 0x98 bytes, ARM
 * func_020ed73c @ 0x020ed73c, 0x60 bytes, ARM
 */

extern int func_020ed874(void *a, void *b, unsigned short index, void *c);
extern unsigned char data_021fbef8;
extern int func_020ed834(int a0, int a1, int a2, unsigned int argument3);

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

int func_020ed73c(int a0, int a1, int a2, int a3)
{
    if ((unsigned char) (data_021fbef8 + 0xff) <= 1) {
        return func_020ed834(a0, a1, a2, a3);
    }
    if ((unsigned char) (data_021fbef8 + 0xfd) <= 1) {
        return func_020ed79c((void *) a0, (void *) a1, a2, (void *) a3);
    }
    return 0;
}
