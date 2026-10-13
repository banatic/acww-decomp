/* func_020b5678 @ 0x020b5678, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);
extern void func_020edf54(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5320[];

void *func_020b5678(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020e5320;
    *(volatile unsigned int *) p = (unsigned int) data_020e3c94;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
