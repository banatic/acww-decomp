/* func_ov147_0229a054 @ 0x0229a054, 0x3a bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int, int, int);
extern void func_020356c4(int, int, int, int);

void func_ov147_0229a054(int r0, int r1)
{
    int r4 = r0;
    if (*(unsigned char *) (r0 + 0xa3) == 0) {
        if (r1 != 0) {
            func_02035684(1, 0xf, 0);
            *(unsigned char *) (r4 + 0xa3) = 2;
        } else {
            func_020356c4(2, 0, 0x7f, 0);
            *(unsigned char *) (r4 + 0xa3) = 1;
        }
    }
}
