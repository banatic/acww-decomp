/* func_0208308c @ 0x0208308c, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
