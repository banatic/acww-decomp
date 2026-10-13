/* func_ov147_0229a2dc @ 0x0229a2dc, 0x16 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov147_0229a2d0(void);

void func_ov147_0229a2dc(unsigned int *r0)
{
    unsigned int r1;

    r1 = r0[3];
    if (r1 != 2) {
        r0[2] = r1;
        func_ov147_0229a2d0();
    }
}
