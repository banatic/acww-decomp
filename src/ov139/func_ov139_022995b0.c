/* func_ov139_022995b0 @ 0x022995b0, 0x10 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_ov139_022995b0(unsigned short *r0, unsigned short r1);

unsigned short *func_ov139_022995b0(unsigned short *r0, unsigned short r1)
{
    unsigned short *p;
    unsigned short v;

    p = (unsigned short *) ((char *) r0 + 0x9a0);
    v = *p;
    v |= r1;
    *p = v;
    return p;
}
