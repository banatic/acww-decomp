/* func_020e9ed4 @ 0x020e9ed4, 0xb4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_020ea0a4(void *self);
int func_020e9d64(void *self, int c);
void func_020ea084(void *self);
void OS_Terminate(void);
extern void (*data_021fbe84)(void *self, int ret, int b, int c);
}

class UnkStruct_020e9ed4 {
  public:
    virtual int method0();
    virtual int method1();
    virtual int method2();
    virtual int method3();
    virtual int method4();
    virtual int method5();
    virtual int method6(int b, int c);

    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned int flags;
};

extern "C" int func_020e9ed4(UnkStruct_020e9ed4 *self, int b, int c)
{
    int ret;

    func_020ea0a4(self);
    if (b == -1) {
        b = func_020e9d64(self, c);
    }

    ret = self->method6(b, c);

    if (data_021fbe84 && (self->flags & 0x400)) {
        data_021fbe84(self, ret, b, c);
    }

    if (ret == 0 && (self->flags & 0x4000)) {
        OS_Terminate();
    }

    func_020ea084(self);
    return ret;
}
