/* func_02096c08 @ 0x02096c08, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void func_020ee62c(void *p);
extern __arm void func_020edf54(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e2fe8[];

void *func_02096c08(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020e2fe8;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
