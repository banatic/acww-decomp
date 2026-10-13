/* func_ov122_022a0714 @ 0x022a0714, 0x3c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_0220a568(unsigned int);
extern void func_ov002_02208098(unsigned int, unsigned int);
extern void func_ov122_0229fc2c(unsigned int);
extern void func_ov122_0229f488(unsigned int);

void func_ov122_022a0714(unsigned int param)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_0220a568(param + 0x4010);
        func_ov002_02208098(param, 0x12);
        func_ov122_0229fc2c(param);
    } else {
        func_ov122_0229f488(param);
    }
}
