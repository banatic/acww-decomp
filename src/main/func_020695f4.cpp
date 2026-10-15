/* func_020695f4 @ 0x020695f4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020695f4 {
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
};

extern "C" void func_020a8750(void *);

extern "C" void func_020695f4(char *self)
{
    char *p;
    UnkStruct_020695f4 *obj;
    p = *(char **) (self + 0x24);
    obj = *(UnkStruct_020695f4 **) (p + 0x14a8);
    func_020a8750(self + 0x38);
    obj->v17();
}
