/* func_0209646c @ 0x0209646c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077898(void);

void func_0209646c(int r0, unsigned short *r4, int *r6)
{
    int r5 = r0;
    int r2 = *r6;
    unsigned char r0_2;

    r0 = func_02077898();
    *r4 = (unsigned short) r0;
    r0_2 = *(unsigned char *) (r5 + 2);
    *r6 = r0_2;
}
