/* func_ov146_0229a464 @ 0x0229a464, 0x2c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *param_0x15cc);
extern unsigned char *func_ov002_02208098(void *param, unsigned char value);

void func_ov146_0229a464(unsigned char *param)
{
    func_ov002_0220a164(param + 0x15cc);
    param[0xb3] = param[0x8d];
    func_ov002_02208098(param, 8);
}
