/* func_02002ec0 @ 0x02002ec0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void G3X_Reset(void);

void func_02002ec0(void)
{
    G3X_Reset();
    *(volatile unsigned int *) 0x04000440 = 3;
    *(volatile unsigned int *) 0x04000454 = 0;
    *(volatile unsigned int *) 0x04000440 = 2;
}
