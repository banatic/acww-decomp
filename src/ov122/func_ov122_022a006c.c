/* func_ov122_022a006c @ 0x022a006c, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern void func_ov122_0229f2d0(int);
extern void func_ov122_022a0df8(int);

int func_ov122_022a006c(int param)
{
    if ((data_021fbe40[1] & 8) == 0) {
        return 0;
    }
    func_ov122_0229f2d0(param);
    func_ov122_022a0df8(param);
    return 1;
}
