/* func_ov125_0229ffc4 @ 0x0229ffc4, 0x3c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov125_0229f948(int);
extern int func_ov002_02208e28(int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov125_0229ffc4(int param)
{
    int r4 = param;
    if (func_ov002_02208e28(r4 + 0x180) != 0) {
        if (func_0206fe54() != 0) {
            func_ov125_0229f948(r4);
            func_ov002_02208098(r4, 3);
        } else {
            func_ov002_02208098(r4, 1);
        }
    }
}
