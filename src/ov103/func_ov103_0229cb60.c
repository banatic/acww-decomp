/* func_ov103_0229cb60 @ 0x0229cb60, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229cdfc(void);
extern int func_ov103_0229cde8(int, int);
extern void func_ov094_0229b938(int, int);

void func_ov103_0229cb60(int r4, int r5)
{
    if (func_ov103_0229cdfc() != 0) {
        func_ov094_0229b938(r4 + 0xb2c, func_ov103_0229cde8(r4, r5));
    }
}
