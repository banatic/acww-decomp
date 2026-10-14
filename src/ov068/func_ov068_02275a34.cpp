/* func_ov068_02275a34 @ 0x02275a34, 0x9c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern unsigned int __ptmf_null[2];
void func_02030864(int);
void func_0205ba64(void *);
void *func_0205b91c(void *, void *);
void func_020b23d4(void *);
int func_0207f270(int);
int func_02079540(int, int);
void func_020044c0(void *, unsigned int, unsigned int, unsigned int);
void func_0205ba60(void *);
}

class UnkStruct_02275a34 {
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
    virtual int v25() = 0;

    unsigned char pad_v[0x510 - 0x4];
    unsigned char unk_510;
    unsigned char pad_511[0x514 - 0x511];
    unsigned char region514[0xa44 - 0x514];
    unsigned int unk_A44;
    unsigned int unk_A48;
    void *unk_A4C;
    unsigned char pad_A50[0xa54 - 0xa50];
    void *unk_A54;
    unsigned char pad_A58[0xa61 - 0xa58];
    unsigned char unk_A61;
};

extern "C" int func_ov068_02275a34(UnkStruct_02275a34 *self)
{
    unsigned char tmp[0x18];
    void *p;

    *(double *) &self->unk_A44 = *(double *) __ptmf_null;
    self->unk_510 = 0;
    func_02030864(0);

    func_0205ba64(tmp);
    p = func_0205b91c(tmp, &self->unk_A4C);
    self->unk_A54 = p;
    func_020b23d4(p);

    if (self->v25()) {
        func_02079540(func_0207f270(self->v25()), 2);
    }

    self->unk_A61 = 0x1e;
    func_020044c0(self->region514, 0x4ca, 0x7f, 0);
    func_0205ba60(tmp);
    return 1;
}