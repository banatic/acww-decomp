/* func_ov003_0221df74 @ 0x0221df74, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
}
class UnkStruct_0221df74 {
  public:
    virtual void *v0() = 0;
    virtual void *v1() = 0;
    virtual void *v2() = 0;
    virtual void *v3() = 0;
    virtual void *v4() = 0;
    virtual void *v5() = 0;
    virtual void *v6() = 0;
    virtual void *v7() = 0;
    virtual void *v8() = 0;
    virtual void *v9() = 0;
    virtual void *v10() = 0;
    virtual void *v11() = 0;
    virtual void *v12() = 0;
    virtual void *v13() = 0;
    virtual void *v14() = 0;
    virtual void *v15() = 0;
    virtual void *v16() = 0;
    virtual void *v17() = 0;
    virtual void *v18() = 0;
    virtual void *v19() = 0;
    virtual void *v20() = 0;
    virtual void *v21() = 0;
    virtual void *v22() = 0;
    virtual void *v23() = 0;
    virtual void *v24() = 0;
    virtual void *v25() = 0;
    virtual void *v26() = 0; // vtable offset 0x68
};

extern "C" void func_02055060(void *a, void *b, int c, int d, unsigned short e, int f);
extern "C" void func_ov009_02262ef0(void *a, int b);

extern "C" int func_ov003_0221df74(void *obj)
{
    UnkStruct_0221df74 *c = (UnkStruct_0221df74 *) obj;
    void *r1 = c->v26();
    void *r2 = c->v26();
    unsigned short w = (unsigned short) (*((unsigned short *) ((char *) r1 + 4)) - 1);
    func_02055060((char *) obj + 0x13c, r2, 3, 0x1000, w, 0);
    func_ov009_02262ef0((char *) obj + 0x238, 0x81a);
    return 1;
}
