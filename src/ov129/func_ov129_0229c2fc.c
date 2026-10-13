/* func_ov129_0229c2fc @ 0x0229c2fc, 0x2c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(unsigned char *p);
extern void func_ov002_02208098(unsigned char *p, int n);

void func_ov129_0229c2fc(unsigned char *param)
{
    func_ov002_0220a164(param + 0x3a0);
    param[0xac] = param[0x8d];
    func_ov002_02208098(param, 9);
}
