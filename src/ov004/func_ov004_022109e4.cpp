/* func_ov004_022109e4 @ 0x022109e4, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022109e4 {
  public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual void v27() = 0;
    virtual void v28() = 0;
    virtual void v29() = 0;
    virtual void v30() = 0;
    virtual void v31() = 0;
    virtual void v32() = 0;
    virtual void v33() = 0;
    virtual int v34() = 0;
};

extern "C" {
int func_020033ec(void *arg0);
int func_ov004_0220e5c8(void *self);
void func_0205510c(void *p, void *q);
void func_ov004_0220d7cc(void *p, void *self);
}
extern int NNS_G3dGlb[];

extern "C" int func_ov004_022109e4(UnkStruct_022109e4 *selfp)
{
    char *self = (char *) selfp;
    int save[4];
    unsigned int j;

    if (func_020033ec((void *) selfp) == 0) {
        return 0;
    }
    if (selfp->v34() == 0) {
        return 0;
    }
    if (*(int *) (self + 0x150) != 0 || *(int *) (self + 0x154) != 0 || *(int *) (self + 0x158) != 0) {
        if (func_ov004_0220e5c8(self) != 0) {
            for (j = 0; j < 4; j++) {
                save[j] = *(int *) ((char *) &NNS_G3dGlb[j] + 0xa8);
                *(int *) ((char *) &NNS_G3dGlb[j] + 0xa8) = (j << 30) | 0x7fff;
            }
        }
        func_0205510c(self + 0x538, self + 0x150);
        if (func_ov004_0220e5c8(self) != 0) {
            for (j = 0; j < 4; j++) {
                *(int *) ((char *) &NNS_G3dGlb[j] + 0xa8) = save[j];
            }
        }
    }
    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0220d7cc(self + 0x18c, self);
    }
    return 1;
}
