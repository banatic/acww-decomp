/* func_02051b34 @ 0x02051b34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020dcf40[];

void *func_02051b34(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020dcf40;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
