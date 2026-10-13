/* func_020565ec @ 0x020565ec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020dd184;
extern unsigned int data_020dd154;

void func_020565ec(unsigned int *r0)
{
    unsigned int r1;
    unsigned int r2;

    r1 = (unsigned int) &data_020dd184;
    *r0 = r1;
    r2 = 0;
    *(r0 + 2) = r2;
    *(r0 + 3) = r2;
    r1 = 0x1000;
    *(r0 + 4) = r1;
    r1 = (unsigned int) &data_020dd154;
    *r0 = r1;
    *(r0 + 7) = r2;
    *(r0 + 6) = r2;
}
