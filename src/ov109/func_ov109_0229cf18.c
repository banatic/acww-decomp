/* func_ov109_0229cf18 @ 0x0229cf18, 0x3c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov109_0229c6ac(int);
extern void func_ov002_02208098(int, int);
extern int func_ov002_02208e28(int);

void func_ov109_0229cf18(int r0)
{
    int r4 = r0;
    if (func_ov002_02208e28(r4 + 0x22d8) != 0) {
        if (func_0206fe54() != 0) {
            func_ov109_0229c6ac(r4);
            func_ov002_02208098(r4, 6);
        } else {
            func_ov002_02208098(r4, 4);
        }
    }
}
