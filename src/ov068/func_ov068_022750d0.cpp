/* func_ov068_022750d0 @ 0x022750d0, 0x70 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022750d0 {
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
    virtual void v24(int arg);
    char pad_04[0x28c];
    int unk_290;
    int unk_294;
    char unk_298;
    char pad_299[3];
    int unk_29C;
    char pad_2A0[180];
    int unk_354;
    char pad_358[160];
    int unk_3F8;
};

extern UnkStruct_022750d0 *data_ov068_022788b0;
extern "C" void func_ov004_0222c590(UnkStruct_022750d0 *p, int arg);
extern "C" void func_ov004_0222c5c8(UnkStruct_022750d0 *p, int *arg);
extern "C" void func_ov004_0222c62c(void *a, void *b, void *c, void *d);

extern int data_ov068_02277fa4;
extern int data_ov068_02277fb0;

extern "C" int func_ov068_022750d0(UnkStruct_022750d0 *p)
{
    data_ov068_022788b0 = p;
    func_ov004_0222c590(p, 1);
    func_ov004_0222c5c8(p, &data_ov068_02277fa4);
    p->unk_294 = 1;
    p->unk_290 = p->unk_294;
    func_ov004_0222c62c(&data_ov068_02277fb0, &p->unk_29C, &p->unk_354, &p->unk_3F8);
    p->v24(1);
    p->unk_298 = 1;
    return 1;
}
