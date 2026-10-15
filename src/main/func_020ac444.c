/* func_020ac444 @ 0x020ac444, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020ac444(void *receiver)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x0400000A;

    *reg &= ~3;
    *reg = (*reg & 0x43) | 0x500;
    *reg &= ~0x40;
}
