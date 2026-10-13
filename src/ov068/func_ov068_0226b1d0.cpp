/* func_ov068_0226b1d0 @ 0x0226b1d0, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_0207f270(int);
int func_0207f294(int);
int func_ov003_02220318(int);
void func_02019c20(void *, int, int, int, int, int);
void func_02079540(int, int, int _x);
void func_020794d4(int, int);
}

class UnkStruct_0226b1d0_2 {
  public:
    virtual void D00() = 0;
    virtual void D01() = 0;
    virtual void D02() = 0;
    virtual void D03() = 0;
    virtual void D04() = 0;
    virtual void D05() = 0;
    virtual void D06() = 0;
    virtual void D07() = 0;
    virtual void D08() = 0;
    virtual void D09() = 0;
    virtual void D10() = 0;
    virtual void D11() = 0;
    virtual void D12() = 0;
    virtual void D13() = 0;
    virtual void D14() = 0;
    virtual void D15() = 0;
    virtual void D16() = 0;
    virtual void D17() = 0;
    virtual void D18() = 0;
    virtual void D19() = 0;
    virtual void D20() = 0;
    virtual void D21() = 0;
    virtual void D22() = 0;
    virtual void D23() = 0;
    virtual void D24() = 0;
    virtual int Call() = 0;

    unsigned char pad_04[0x55d];
    unsigned char unk_561;
    unsigned char unk_562;
    unsigned char pad_563;
    void *unk_564;
    unsigned char pad_568[0x348];
    int unk_8B0;
    int unk_8B4;
};

extern "C" void func_0201c3f4(UnkStruct_0226b1d0_2 *, int);

extern struct UnkStruct_0226b1d0 {
    int a;
    int b;
} data_ov068_02276f50;

extern "C" void func_ov068_0226b1d0(void *arg0, UnkStruct_0226b1d0_2 *obj)
{
    int v = obj->Call();
    int a = func_0207f270(v);

    if (func_ov003_02220318(func_0207f294(v)) != 0) {
        func_02019c20(&obj->unk_564, 2, 0x3d, 1, 1, 0);
        int a0 = data_ov068_02276f50.a;
        int b0 = data_ov068_02276f50.b;
        obj->unk_8B0 = a0;
        obj->unk_8B4 = b0;
        func_02079540(a, 1, a0);
        func_020794d4(a, 0);
        obj->unk_561 = 1;
        obj->unk_562 = 1;
        func_0201c3f4(obj, 0);
        ((unsigned char *) arg0)[0x1c] = 1;
    }
}