/* func_0203f0b8 @ 0x0203f0b8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ce0(int, void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020d7244[];
extern unsigned char data_020da13c[];
extern unsigned char data_020dab34[];
extern unsigned char data_0213ff78[];

void *func_0203f0b8(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020dab34;
    *(volatile unsigned int *) p = (unsigned int) data_020d7244;
    func_020e8ce0((unsigned int) data_0213ff78, (char *) p + 0x50);
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
