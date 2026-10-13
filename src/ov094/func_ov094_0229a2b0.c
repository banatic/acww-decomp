/* func_ov094_0229a2b0 @ 0x0229a2b0, 0x1e bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_02299c40(void *);

void func_ov094_0229a2b0(void *r0, unsigned char r1)
{
    unsigned char *r4 = (unsigned char *) r0;
    r4[0xe] = r1;
    *(unsigned short *) (r4 + 8) = 0;
    func_ov094_02299c40(r4);
    r4[0xf] = 2;
    r4[0x10] = 2;
    r4[0x14] = 8;
}
