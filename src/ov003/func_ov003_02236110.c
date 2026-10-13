/* func_ov003_02236110 @ 0x02236110, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_02236110(unsigned short *p)
{
    unsigned int i;
    for (i = 0; i < 0x10; i++) {
        p[i] = 0;
    }
    p[0x10] = 0x100;
}
