/* func_ov004_0222d69c @ 0x0222d69c, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203750c();
extern int func_02037594();
extern void NNS_G3dBindMdlPltt();
extern void NNS_G3dBindMdlTex();
extern int func_ov004_0222c33c();
extern int func_ov004_0222c3a0();

int func_ov004_0222d69c(char *self)
{
    // DECLS
    int v1;
    int v5;
    int v9;
    int v12;
    // ENDDECLS
    v1 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlTex(v1, func_02037594(func_0203750c(v1)));
    v5 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlPltt(v5, func_02037594(func_0203750c(v5)));
    v9 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlTex(v9, func_ov004_0222c33c(self + 0x248));
    v12 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlPltt(v12, func_ov004_0222c33c(self + 0x248));
    return 0x1;
}
