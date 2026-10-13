/* func_ov094_0229a4d8 @ 0x0229a4d8, 0x34 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(unsigned char *p);

void func_ov094_0229a4d8(unsigned char *self)
{
    int i;
    for (i = 0; i < 3; i++) {
        func_020b9ccc(self + 0x98c + i * 0x38);
    }
    self[0xa58] = 0;
}
