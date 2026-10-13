/* func_02096c30 @ 0x02096c30, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *) __attribute__((arm));

extern unsigned char data_020da13c[];
extern unsigned char data_020e2fe8[];

void *func_02096c30(void *ptr)
{
    volatile unsigned int *p = (volatile unsigned int *) ptr;
    *p = (unsigned int) data_020e2fe8;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
