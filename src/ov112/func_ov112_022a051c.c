/* func_ov112_022a051c @ 0x022a051c, 0x2c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern void func_ov112_0229f3e0(void *);
extern void func_ov112_022a0068(void *);

int func_ov112_022a051c(void *param)
{
    if (!(data_021fbe40[1] & 8)) {
        return 0;
    } else {
        func_ov112_0229f3e0(param);
        func_ov112_022a0068(param);
        return 1;
    }
}
