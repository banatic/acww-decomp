/* func_02089954 @ 0x02089954, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *dest, unsigned int size);

extern unsigned char data_021d2920[];
extern unsigned char data_021d2d20[];

void func_02089954(void)
{
    DC_FlushRange((void *) data_021d2920, 0x400);
    DC_FlushRange((void *) data_021d2d20, 0x400);
}
