/* func_ov129_0229c820 @ 0x0229c820, 0x26 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229b7dc(int, int);
extern int func_0206fe60(void);
extern void func_ov129_0229c874(int);
extern void func_ov129_0229c848(int);

void func_ov129_0229c820(int r0)
{
    int r4 = r0;
    func_ov129_0229b7dc(r4, 0x80);
    if (func_0206fe60() != 0) {
        func_ov129_0229c874(r4);
    } else {
        func_ov129_0229c848(r4);
    }
}
