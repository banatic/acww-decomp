/* func_020ee4d8 @ 0x020ee4d8, 0x78 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern "C" void func_020e8dbc(void *, void *);
extern "C" void func_020e8ce0(void *, void *);
extern "C" void func_020e9fc8(void *);
extern "C" void func_020eebb4(void *);

extern char data_021fcff8[];
extern char data_021fd034[];

class UnkStruct_020ee4d8 {
  public:
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
    virtual void target_virtual();
    char pad_04[16];
    void *unk_14;
    char pad_18[16];
    void *unk_28;
    char pad_2C[28];
    void *unk_48;
    void *unk_4C;
};

extern "C" void func_020ee4d8(UnkStruct_020ee4d8 *p, int marker)
{
    if (marker != 2) {
        return;
    }
    func_020e8dbc(data_021fcff8, (char *) p + 0x14);
    func_020e8ce0(data_021fd034, (char *) p + 0x28);
    if (p->unk_4C != 0) {
        func_020e9fc8(p->unk_4C);
    }
    if (p->unk_48 != 0) {
        func_020eebb4(p->unk_48);
    }
    if (p == 0) {
        return;
    }
    p->target_virtual();
    return;
}
