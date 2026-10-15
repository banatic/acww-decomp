/* func_ov004_0222c66c @ 0x0222c66c, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222c66c {
    int a;
    ~UnkStruct_0222c66c() {}
};

extern "C" {
extern int func_ov004_0222c3f4(void *, void *);
extern int func_ov004_0222c348(void *, void *);
extern void *func_ov004_0222c3a0(void *);
extern void *func_ov004_0222c33c(void *);
extern int func_02055f2c(void *, void *, int);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);
}
extern "C" int func_ov004_0222c66c(void *a, void *b, void *c, void *d, void *e)
{
    UnkStruct_0222c66c t;
    func_ov004_0222c3f4(d, a);
    func_ov004_0222c348(e, b);
    func_02055f2c(c, func_ov004_0222c3a0(d), 0);
    NNS_G3dBindMdlTex(func_ov004_0222c3a0(d), func_ov004_0222c33c(e));
    return NNS_G3dBindMdlPltt(func_ov004_0222c3a0(d), func_ov004_0222c33c(e));
}
