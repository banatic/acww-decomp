/* func_02068e04 @ 0x02068e04, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001da0(int);
extern void func_02001d1c(int);

void func_02068e04(void)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x0400000c;
    unsigned int v;

    v = *reg;
    v &= ~3;
    v |= 1;
    *reg = (unsigned short) v;

    v = *reg;
    v &= 0x43;
    v |= 0x600;
    *reg = (unsigned short) v;

    v = *reg;
    v &= ~0x40;
    *reg = (unsigned short) v;

    func_02001da0(0x1f);
    func_02001d1c(0x1b);
}
