/* func_02059c80 @ 0x02059c80, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void func_020ee660(void);
extern void func_020f5958(void *ptr);
extern int data_020da13c;
extern int data_020dd33c;

void *func_02059c80(void)
{
    void *p = func_020edf70(0x11c);
    if (p) {
        func_020ee660();
        *(volatile void **) p = (void *) &data_020da13c;
        *(volatile void **) p = (void *) &data_020dd33c;
        *(volatile unsigned short *) ((char *) p + 0x50) = 0xfff1;
        func_020f5958((char *) p + 0xdc);
    }
    return p;
}
