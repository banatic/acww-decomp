/* func_ov096_0229fbbc @ 0x0229fbbc, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

void func_ov096_0229fbbc(void *param)
{
    extern void func_ov096_0229dea4(void *);
    extern void func_ov096_0229eb14(void *);
    extern void func_ov096_0229ed74(void *, unsigned char);
    extern void func_ov002_02207fc0(void *);
    extern void func_ov002_02208098(void *, int);

    unsigned char *p = (unsigned char *) param;
    p[0xb3] = 0x26;
    func_ov096_0229dea4(param);
    func_ov002_02207fc0(param);
    func_ov096_0229eb14(param);
    func_ov002_02208098(param, 0xa);
    func_ov096_0229ed74(param, p[0xb5]);
}
