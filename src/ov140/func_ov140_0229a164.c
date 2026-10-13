/* func_ov140_0229a164 @ 0x0229a164, 0x40 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_02299888(unsigned char *a, int b, int c, int d, int e);

void func_ov140_0229a164(unsigned char *base, int something)
{
    int local;
    int i;
    for (i = 0; i < 6; i++) {
        if (*(base + i + 0x8e0) == 4) {
            local = 8;
        } else {
            local = 14;
        }
        func_ov139_02299888(base + 0x8e8, i, something, 5, local);
    }
}
