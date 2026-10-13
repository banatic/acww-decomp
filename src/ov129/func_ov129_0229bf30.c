/* func_ov129_0229bf30 @ 0x0229bf30, 0x24 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_02299a00(unsigned char *p, int idx, unsigned char byte);
extern unsigned char data_ov129_0229dae0[];

int func_ov129_0229bf30(unsigned char *p, int idx)
{
    return func_ov127_02299a00(p + 0x734, idx, data_ov129_0229dae0[(p + idx)[0x2f98]]);
}
