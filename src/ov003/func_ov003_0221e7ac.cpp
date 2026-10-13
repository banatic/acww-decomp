/* func_ov003_0221e7ac @ 0x0221e7ac, 0x118 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void *g_021c9b1c;
void *g_020ccf94;
int func_ov009_02264cf8(void *self, int param);
int func_0205650c(void *ptr, int val, void *glob);
void func_02056478(void *ptr, int val, int a, int b, int c);
int func_02055e00(void *ptr);
void func_020563dc(void *ptr, int val);
int func_ov003_02220150(void *self);
int func_020b6590(int val);
void func_020b7d84(int a, void *b, int *c, int d, int e, int f);
int func_020b6660(void);
int func_02073d90(void *ptr);
int func_02073918(void *ptr, int param);
void func_ov003_0221e580(void *self, int param);
int func_ov003_0221e6a0(void *self);
int func_020b312c(unsigned short v);
}

class UnkStruct_0221e7ac {
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
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual void method(int arg) = 0;
    char pad_04[0x58];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0xce];
    unsigned short unk_136;
    char pad_138[0x4];
    char unk_13C;
    char pad_13D[0x5b];
    int unk_198;
    char pad_19C[0x11c];
    char unk_2B8;
    char pad_2B9[0x1f];
    char unk_2D8;
    char pad_2D9[0x1b];
    char unk_2F4;
};

extern "C" int func_ov003_0221e7ac(UnkStruct_0221e7ac *self)
{
    if (func_ov009_02264cf8(self, 0) != 0) {
        if (func_0205650c(&self->unk_2B8, self->unk_198, g_021c9b1c) != 0) {
            int val = func_ov009_02264cf8(self, 0);
            func_02056478(&self->unk_2B8, val, 1, 0x1000, 0);
            int val2 = func_02055e00(&self->unk_13C);
            func_020563dc(&self->unk_2B8, val2);
        }
    }
    int mask = (unsigned char) func_ov003_02220150(self);
    int arr[3];
    arr[0] = self->unk_5C;
    arr[1] = self->unk_60;
    arr[2] = self->unk_64;
    arr[1] += 0x1000;
    int ret = func_020b6590(arr[1]);
    func_020b7d84(ret, &self->unk_2D8, arr, 0x1000, 7, mask);
    self->unk_2F4 = 1;
    if (func_020b6660() == 0) {
        self->unk_2F4 = 0;
    } else {
        void *global = g_020ccf94;
        if (func_02073d90(global) != 0 && func_02073918(global, 0) == 0) {
            self->unk_2F4 = 0;
        }
    }
    func_ov003_0221e580(self, 0);
    if (func_ov003_0221e6a0(self) != 0) {
        self->method(0);
    } else {
        int v = func_020b312c(self->unk_136);
        self->method(v);
    }
    return 1;
}
