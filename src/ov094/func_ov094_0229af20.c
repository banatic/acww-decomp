/* func_ov094_0229af20 @ 0x0229af20, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a4d8(unsigned char *);

void func_ov094_0229af20(unsigned char *param)
{
    func_ov094_0229a4d8(param);
    if (param[0xa57] != 0) {
        --param[0xa57];
    }
}
