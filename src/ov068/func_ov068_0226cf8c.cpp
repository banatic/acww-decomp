/* func_ov068_0226cf8c @ 0x0226cf8c, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226cf8c {
  public:
    virtual int v00();
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
    virtual int v09();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int mTarget();
};

extern "C" int func_0208150c(int);
extern "C" int func_02003704(int);
extern "C" int func_0207f270(int);
extern "C" int func_020794c4(int);

extern "C" unsigned char func_ov068_0226cf8c(UnkStruct_0226cf8c *self)
{
    int result;

    if (self->mTarget() != 0 && func_02003704(func_0208150c(self->mTarget())) != 0) {
        result = func_0207f270(self->mTarget());
    } else {
        result = 0;
    }

    if (result != 0) {
        result = func_020794c4(result);
    } else {
        result = 0;
    }

    return (unsigned char) result;
}
