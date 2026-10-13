/* func_ov068_022672a0 @ 0x022672a0, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern short data_ov068_02278260;

class UnkStruct_022672a0 {
  public:
    virtual int v0() = 0;
    virtual int v1() = 0;
    virtual int v2() = 0;
    virtual int v3() = 0;
    virtual int v4() = 0;
    virtual int v5() = 0;
    virtual int v6() = 0;
    virtual int v7() = 0;
    virtual int v8() = 0;
    virtual int v9() = 0;
    virtual int v10() = 0;
    virtual int v11() = 0;
    virtual int v12() = 0;
    virtual int v13() = 0;
    virtual int v14() = 0;
    virtual int v15() = 0;
    virtual int v16() = 0;
    virtual int v17() = 0;
    virtual int v18(void *other) = 0;
};

extern "C" {
int func_ov068_0226cf8c(void *);
int func_0202e174(void *);
int func_ov068_0226cbe4(void *, int);
int func_0201c350(void *, void *, int);
int func_0203ef00(void *, void *, int, int);
}

extern "C" int func_ov068_022672a0(UnkStruct_022672a0 *self, void *other)
{
    short s = data_ov068_02278260;
    int local = func_ov068_0226cf8c(self);
    int ret = 0;
    if (self->v18(other) != 0 && func_0202e174(self) == 0 && func_ov068_0226cbe4((char *) self + 0x8b8, 0) != 0 &&
        (unsigned) local <= 1 && func_0201c350(self, other, 0x5000) == 0 && func_0201c350(self, other, 0xe000) != 0 &&
        func_0203ef00(self, other, (short) (-s), s) != 0) {
        ret = 1;
    }
    return ret;
}
