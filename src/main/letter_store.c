/* letter_store: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02097f58 @ 0x02097f58, 0x16 bytes, Thumb
 * func_02097f38 @ 0x02097f38, 0x1e bytes, Thumb
 */

extern void func_02066650(void *);

char *func_02097f58(char *base, int index)
{
    if (index >= 0 && index < 2) {
        return base + ((index * 25) << 8);
    }
    return 0;
}

void func_02097f38(void *param)
{
    int i;
    void *p;

    for (i = 0; i < 50; i++) {
        p = (void *) ((unsigned int) param + (i << 8));
        func_02066650(p);
    }
}
