/* func_ov004_02214610 @ 0x02214610, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02214610 {
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
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void vcall(int a, int b);
};

extern "C" void func_ov004_0220d280(void *p, int a, int b);
extern "C" void func_ov004_022107d4(UnkStruct_02214610 *self);
extern "C" int func_ov004_0220e4b0(void *p);
extern "C" void func_02056ffc(void *p);
extern "C" int func_02056f94(void *p);

extern "C" void func_ov004_02214610(UnkStruct_02214610 *self)
{
    func_ov004_0220d280((char *) self + 0x740, 1, 0);
    func_ov004_022107d4(self);
    if (func_ov004_0220e4b0((char *) self + 0x7c4) != 0) {
        func_02056ffc((char *) self + 0x7c4);
        **(int **) ((char *) self + 0x7dc) = *(int *) ((char *) self + 0x7cc);
        if (func_02056f94((char *) self + 0x7c4) != 0) {
            self->vcall(2, 0xff);
        }
    } else {
        self->vcall(2, 0xff);
    }
}
