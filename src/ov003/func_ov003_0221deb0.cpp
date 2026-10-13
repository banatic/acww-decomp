/* func_ov003_0221deb0 @ 0x0221deb0, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct SInner {
    int pad_00;
    unsigned short val;
} SInner;

class UnkStruct_0221deb0 {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual void v9() = 0;
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
    virtual SInner *v25() = 0;
    char pad_04[0x138];
    char unk_13C;
    char pad_13D[0x238 - 0x13c - 1];
    char unk_238;
};

extern "C" void func_02055060(void *p, void *b, int y, int z, unsigned short w, int r);
extern "C" void func_ov009_02262ef0(void *p, int x);

extern "C" int func_ov003_0221deb0(UnkStruct_0221deb0 *obj)
{
    SInner *a = obj->v25();
    SInner *b = obj->v25();
    unsigned short v = (unsigned short) (a->val - 1);
    func_02055060(&obj->unk_13C, b, 3, 0x1000, v, 0);
    func_ov009_02262ef0(&obj->unk_238, 0x81b);
    return 1;
}
