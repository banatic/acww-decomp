/* func_ov132_0229adb8 @ 0x0229adb8, 0x2c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov132_0229adb8(unsigned char *p)
{
    int i;
    p[0x1504] = 0;
    for (i = 0; i < 2; i++) {
        func_02070b84(p + 0x2c4 + i * 0x6c);
    }
}
