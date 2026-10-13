/* func_020492c8 @ 0x020492c8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020493b4(void *addr, int param, int i, int j);

void func_020492c8(void *base, int arg)
{
    int i = 0;
    int j;

    for (j = 0; j < 2; j++) {
        i = 0;
        do {
            func_020493b4((char *) base + i * 0x510 + j * 0x288, arg, i, j);
            i++;
        } while (i < 2);
    }
}
