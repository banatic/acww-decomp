/* func_020364ec @ 0x020364ec, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036560(void *);

void func_020364ec(void *param)
{
    int i;
    void *p;
    unsigned int *ptr;

    p = param;
    for (i = 0; i < 8; i++) {
        func_02036560((char *) p + 4 + (i << 4));
    }
    ptr = (unsigned int *) ((char *) p + 0x84);
    *ptr = 0;
}
