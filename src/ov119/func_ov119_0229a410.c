/* func_ov119_0229a410 @ 0x0229a410, 0xe bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229a410(unsigned short *r0, unsigned short r1);

void func_ov119_0229a410(unsigned short *r0, unsigned short r1)
{
    unsigned short r2;
    r2 = *(unsigned short *) ((char *) r0 + 0x98);
    r2 |= r1;
    *(unsigned short *) ((char *) r0 + 0x98) = r2;
}
