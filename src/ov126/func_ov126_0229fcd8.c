/* func_ov126_0229fcd8 @ 0x0229fcd8, 0x24 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern int func_ov126_022a0a90(int);

int func_ov126_0229fcd8(int arg)
{
    if (!(data_021fbe40[1] & 8)) {
        return 0;
    }
    func_ov126_022a0a90(arg);
    return 1;
}
