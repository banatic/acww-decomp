/* func_ov009_022655d4 @ 0x022655d4, 0x1e bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022655d4 {
    char pad_00;
    unsigned char byte;
};
struct UnkStruct_022655d4_2;
class UnkStruct_022655d4_3 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24(int, UnkStruct_022655d4_2 *);
};
struct UnkStruct_022655d4_4 {
    char pad_00[0x2c];
    UnkStruct_022655d4_3 *sub;
};
struct UnkStruct_022655d4_2 {
    UnkStruct_022655d4 *s;
    UnkStruct_022655d4_4 *obj;
};

extern "C" void func_ov009_022655d4(UnkStruct_022655d4_2 *p)
{
    UnkStruct_022655d4_3 *sub = p->obj->sub;
    if (sub) {
        sub->v24(p->s->byte, p);
    }
}
