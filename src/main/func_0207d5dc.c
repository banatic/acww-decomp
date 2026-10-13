/* func_0207d5dc @ 0x0207d5dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ffa0(void);

void func_0207d5dc(int param1, int param2)
{
    int r5;
    int r4;
    int r0;
    unsigned short *r0_ptr;
    unsigned short r2;
    int r1;

    r5 = param1;
    r4 = param2;
    r0 = func_0207ffa0();
    if (r0 != 0) {
        r0_ptr = (unsigned short *) (r5 + 0x7d0);
        r2 = *r0_ptr;
        r1 = 1 << r4;
        r2 &= ~r1;
        *r0_ptr = r2;
    }
}
