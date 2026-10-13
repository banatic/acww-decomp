/* func_020a1810 @ 0x020a1810, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *const data_021f3c3c;

int func_020a1810(void)
{
    unsigned int *p = data_021f3c3c;

    if (p != 0) {
        if (*(unsigned int *) ((char *) p + 0x50) == 0) {
            return 1;
        }
    }
    return 0;
}
