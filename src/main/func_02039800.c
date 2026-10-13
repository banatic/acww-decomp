/* func_02039800 @ 0x02039800, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02039358(void *ptr);

extern unsigned char data_021c6738[];

void *func_02039800(void)
{
    return func_02039358(*(void **) data_021c6738);
}
