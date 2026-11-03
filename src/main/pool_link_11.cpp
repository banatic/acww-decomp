/* pool_link_11: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208308c @ 0x0208308c, 0x42 bytes, Thumb
 * func_02083068 @ 0x02083068, 0x24 bytes, Thumb
 */

class UnkStruct_0208308c;

class UnkStruct_0208308c_2 {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual UnkStruct_0208308c *getB();
    signed char b;
};

class UnkStruct_0208308c {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void setVal(int);
    unsigned int limit;
};

extern "C" int func_02083bfc(UnkStruct_0208308c *);

struct UnkStruct_02083068;

struct UnkStruct_02083068_2 {
    virtual void v0();
    virtual void v1();
    virtual UnkStruct_02083068 *v2();
    signed char unk_04;
};

struct UnkStruct_02083068 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3(signed char c);
};

extern "C" int func_0208308c(UnkStruct_0208308c_2 *p)
{
    UnkStruct_0208308c *x = p->getB();
    int ret = 0;
    if (x != 0) {
        if (p->b == -1) {
            int val = func_02083bfc(x);
            if ((unsigned) val < x->limit) {
                p->b = (char) val;
                x->setVal(p->b);
                ret = 1;
            }
        } else {
            ret = 1;
        }
    }
    return ret;
}

extern "C" void func_02083068(UnkStruct_02083068_2 *this_)
{
    UnkStruct_02083068 *b;
    signed char c;
    b = this_->v2();
    if (b != 0) {
        c = this_->unk_04;
        b->m3(c);
        this_->unk_04 = -1;
    }
}
