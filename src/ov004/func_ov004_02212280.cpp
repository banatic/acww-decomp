/* func_ov004_02212280 @ 0x02212280, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02212280 {
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
    virtual void v28(int, int) = 0;
};

extern "C" {
void func_ov004_0221041c(void *self, int a, int b, int c, int d);
int func_ov004_0220d2b8(void *p);
void func_ov004_0220d0a0(void *p, int a, int b);
void func_02052738(void *self, int a, int b, int c);
int func_ov004_0223c10c(void);
}

extern "C" int func_ov004_02212280(UnkStruct_02212280 *self)
{
    int a;

    func_ov004_0221041c(self, 0, 1, 0x1000, 0);
    a = *(int *) ((char *) self + 0x594);
    func_ov004_0220d0a0((char *) self + 0x844, a, func_ov004_0220d2b8((char *) self + 0x740));
    if (*(int *) ((char *) self + 0x76c) == 1) {
        func_02052738(self, 0, 0xff, 1);
    } else if (func_ov004_0220d2b8((char *) self + 0x740) != 0 && func_ov004_0223c10c() == 0) {
        self->v28(1, 0xff);
    } else {
        self->v28(0, 0xff);
    }
    return 1;
}
