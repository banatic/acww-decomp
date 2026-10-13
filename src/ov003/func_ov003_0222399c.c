/* func_ov003_0222399c @ 0x0222399c, 0x68 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02223208(char *p);

void func_ov003_0222399c(char *base)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            func_ov003_02223208(base + i * 0x530 + j * 0x14c);
        }
    }

    for (i = 0; i < 4; i++) {
        func_ov003_02223208(base + 0xf90 + i * 0x14c);
        func_ov003_02223208(base + 0x18a4 + i * 0x14c);
    }
}
