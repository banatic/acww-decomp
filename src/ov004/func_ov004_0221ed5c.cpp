/* func_ov004_0221ed5c @ 0x0221ed5c, 0xc0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int a, b;
} UnkStruct_0221ed5c;

class UnkStruct_0221ed5c_2 {
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
    virtual void v24();
    virtual int check();
    char pad_04[0x898 - 4];
    int unk_898;
    int unk_89C;
};

extern "C" UnkStruct_0221ed5c data_ov004_02253954;
extern "C" char data_ov004_022476cc;
extern "C" char data_ov004_022476c8;
extern "C" void *data_020ccf94;

extern "C" int func_0202e1fc(UnkStruct_0221ed5c_2 *self);
extern "C" void func_02013c0c(char *p);
extern "C" int func_0201c0e0(UnkStruct_0221ed5c_2 *self);
extern "C" void func_ov004_0221eb6c(char *p, UnkStruct_0221ed5c_2 *self, int k);
extern "C" void func_0202c57c(UnkStruct_0221ed5c_2 *self, char *a, char *b, int k);
extern "C" int func_02073dd4(void *g, int k);
extern "C" int func_0207f270(int a);
extern "C" int func_02079544(int a);
extern "C" void func_02079540(int a, int b);

extern "C" int func_ov004_0221ed5c(UnkStruct_0221ed5c_2 *self)
{
    void *g;
    int ta, tb;

    if (func_0202e1fc(self) == 0) {
        return 0;
    }
    ta = data_ov004_02253954.a;
    tb = data_ov004_02253954.b;
    self->unk_898 = ta;
    self->unk_89C = tb;
    func_02013c0c((char *) self + 0x558);
    if (func_0201c0e0(self) != 0) {
        func_ov004_0221eb6c((char *) self + 0x8a0, self, 0);
        func_0202c57c(self, &data_ov004_022476cc, &data_ov004_022476c8, 0);
    } else {
        func_ov004_0221eb6c((char *) self + 0x8a0, self, 3);
    }
    g = data_020ccf94;
    if (func_02073dd4(g, *(int *) ((char *) g + 0x64)) == 0) {
        if (self->check() != 0) {
            if (func_02079544(func_0207f270(self->check())) == 1) {
                func_02079540(func_0207f270(self->check()), 0);
            }
        }
    }
    return 1;
}
