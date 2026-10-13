/* func_0204b160 @ 0x0204b160, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204b160(void *r0);

void func_0204b160(void *r0)
{
    unsigned int *p = (unsigned int *) r0;
    unsigned int zero = 0;
    unsigned int ones;

    p[0] = zero;
    p[1] = zero;

    ones = ~zero;
    p[0] = ones;
    p[1] = ones;
    p[2] = ones;
}
