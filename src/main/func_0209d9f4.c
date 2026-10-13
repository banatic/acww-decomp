/* func_0209d9f4 @ 0x0209d9f4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e360c[];

volatile int *func_0209d9f4(volatile int *p)
{
    *p = (unsigned int) data_020e360c;
    *p = (unsigned int) data_020da13c;
    func_020ee62c((void *) p);
    func_020edf54((void *) p);
    return p;
}
