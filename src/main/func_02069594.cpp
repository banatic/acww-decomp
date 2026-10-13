/* func_02069594 @ 0x02069594, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020a8750(void *);

struct UnkStruct_02069594 {
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
    virtual void method();
};

struct UnkStruct_02069594_2 {
    char pad_00[0x14a8];
    UnkStruct_02069594 *unk_14A8;
};

struct UnkStruct_02069594_3 {
    char pad_00[0x24];
    UnkStruct_02069594_2 *unk_24;
    char pad_28[0x10];
    char unk_38;
};

extern "C" void func_02069594(UnkStruct_02069594_3 *self)
{
    UnkStruct_02069594 *obj = self->unk_24->unk_14A8;
    func_020a8750(&self->unk_38);
    obj->method();
}
