/* func_02069514 @ 0x02069514, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02069514_2 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual void method();
};

struct UnkStruct_02069514 {
    char pad_00[0x24];
    void **ptr;
    char pad_28[0x10];
};

extern "C" void func_020a8750(void *p);

extern "C" void func_02069514(UnkStruct_02069514 *s)
{
    UnkStruct_02069514_2 *obj = (UnkStruct_02069514_2 *) s->ptr[0x14a8 / 4];
    func_020a8750((char *) s + 0x38);
    obj->method();
}
