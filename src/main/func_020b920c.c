/* func_020b920c @ 0x020b920c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void *ptr);

extern unsigned char data_020da13c[];
extern unsigned char data_020e587c[];

void *func_020b920c(void)
{
    void *p;
    p = func_020edf70(0x50);
    if (p) {
        func_020ee660(p);
        *(volatile unsigned int *) p = (unsigned int) (unsigned int) data_020da13c;
        *(volatile unsigned int *) p = (unsigned int) (unsigned int) data_020e587c;
    }
    return p;
}
