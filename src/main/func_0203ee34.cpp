/* func_0203ee34 @ 0x0203ee34, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203ee34 {
  public:
    virtual void m00(void);
    virtual void m04(void);
    virtual void m08(void);
    virtual void m0c(void);
    virtual void m10(void);
    virtual void m14(void);
    virtual void m18(void);
    virtual void m1c(void);
    virtual void m20(void);
    virtual void m24(void);
    virtual void m28(void);
    virtual void m2c(void);
    virtual void m30(void);
    virtual void m34(void);
    virtual void m38(void);
    virtual void m3c(void);
    virtual void m40(void);
    virtual void m44(void);
    virtual int m48(void *q);
};
extern short data_020ca4cc[];
extern "C" int func_0203ee7c(UnkStruct_0203ee34 *p, void *);
extern "C" int func_0203ef00(UnkStruct_0203ee34 *p, void *q, int d, int v);
extern "C" int func_0203ee34(UnkStruct_0203ee34 *p, void *q);
int func_0203ee34(UnkStruct_0203ee34 *p, void *q)
{
    if (func_0203ee7c(p, q) != 0) {
        short v = data_020ca4cc[0];
        if (func_0203ef00(p, q, (short) -v, v) != 0) {
            return p->m48(q);
        }
    }
    return 0;
}
