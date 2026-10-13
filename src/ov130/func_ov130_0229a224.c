/* func_ov130_0229a224 @ 0x0229a224, 0x28 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_02299d48(void);

int func_ov130_0229a224(unsigned char *r0)
{
    if (r0[2] != 0) {
        r0[2] = r0[2] - 1;
        if (r0[2] == 0) {
            r0[2] = 2;
            func_ov130_02299d48();
            return 1;
        }
    }
    return 0;
}
