/* func_02070400 @ 0x02070400, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int);
extern void func_020ee660(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020df548[];

void *func_02070400(void)
{
    volatile int *p;
    p = (volatile int *) func_020edf70(0x50);
    if (p) {
        func_020ee660((void *) p);
        *p = (int) (unsigned int) data_020da13c;
        *p = (int) (unsigned int) data_020df548;
    }
    return (void *) p;
}
