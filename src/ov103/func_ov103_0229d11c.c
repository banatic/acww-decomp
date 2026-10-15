/* func_ov103_0229d11c @ 0x0229d11c, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov103_0229c6d4(int);
extern int func_ov002_02208e28(int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov103_0229d11c(int r0)
{
    if (func_ov002_02208e28(r0 + 0x22d8) != 0) {
        if (func_0206fe54() != 0) {
            func_ov103_0229c6d4(r0);
            func_ov002_02208098(r0, 9);
        } else {
            func_ov002_02208098(r0, 4);
        }
    }
}
