/* func_0204bd40 @ 0x0204bd40, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(unsigned short *);

int func_0204bd40(unsigned short *argument0)
{
    int r0;
    int r1;

    r0 = func_0204b42c((unsigned short *) argument0);
    r1 = r0 - 0x1000;
    r1 &= 3;
    r0 = r1 + 1;
    return r0;
}
