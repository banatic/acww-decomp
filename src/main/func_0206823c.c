/* func_0206823c @ 0x0206823c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068144(void *ptr);

extern unsigned char data_021cda88[];

void func_0206823c(void)
{
    unsigned int *ptr;
    int i;
    unsigned int *base;

    ptr = (unsigned int *) data_021cda88;
    if (*ptr != 0) {
        i = 0;
        base = ptr;
        do {
            func_02068144((void *) (*base + i * 0x1e9c));
            i++;
        } while (i < 2);
    }
}
