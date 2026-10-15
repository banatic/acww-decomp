/* func_ov004_0222d69c @ 0x0222d69c, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203750c(void);
extern int func_02037594(unsigned int *argument0);
extern int NNS_G3dBindMdlPltt(void *, const void *);
extern int NNS_G3dBindMdlTex(void *, const void *);
extern int func_ov004_0222c33c(void *argument0);
extern int func_ov004_0222c3a0(void *argument0);

int func_ov004_0222d69c(char *self)
{
    // DECLS
    int v1;
    int v5;
    int v9;
    int v12;
    // ENDDECLS
    v1 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlTex((void *) (v1), (const void *) (func_02037594((unsigned int *) (func_0203750c()))));
    v5 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlPltt((void *) (v5), (const void *) (func_02037594((unsigned int *) (func_0203750c()))));
    v9 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlTex((void *) (v9), (const void *) (func_ov004_0222c33c(self + 0x248)));
    v12 = func_ov004_0222c3a0(self + 0x1a4);
    NNS_G3dBindMdlPltt((void *) (v12), (const void *) (func_ov004_0222c33c(self + 0x248)));
    return 0x1;
}
