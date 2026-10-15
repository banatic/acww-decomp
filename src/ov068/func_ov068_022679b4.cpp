/* func_ov068_022679b4 @ 0x022679b4, 0xdc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_022679b4 {
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
    virtual int v25();
};

extern "C" void func_ov068_0226cfd4(void *self);
extern "C" void func_0201651c(void *self, int flag);
extern "C" void func_ov068_02266c34(void *dst, void *src, int a, int b, int c, void *d, int e, u32 f, int g);
extern "C" void func_0202e188(void *self);
extern "C" void func_02013c0c(void *self);
extern "C" int func_0201c2c8(void *self, int val);
extern "C" int func_02019d0c(void *self, int a, int b, int c, int d, int e, int f, int g, int h, u16 i, int j);
extern "C" int func_0203e0a8(void *self, int mode);
extern "C" void func_0203edd0(void *self);
extern "C" void func_0201cbbc(void *self);
extern "C" void func_0207d148(void *obj);

extern u32 data_020c814c;
extern u16 data_020c80f8;

extern unsigned char data_021fbee8[];

extern "C" int func_ov068_022679b4(void *arg0, UnkStruct_022679b4 *arg1)
{
    int result;

    func_ov068_0226cfd4(arg1);
    func_0201651c((char *) arg1 + 0x334, 0);
    func_ov068_02266c34((char *) arg1 + 0x898, arg1, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    func_0202e188(arg1);
    func_02013c0c((char *) arg1 + 0x558);
    result = func_0201c2c8(arg1, 4);
    func_02019d0c((char *) arg1 + 0x564, 3, 1, 0, 0, 0, result, 0, 0, data_020c80f8, 0);
    *(u16 *) ((char *) arg1 + 0xa06) = 0;
    func_0203e0a8(arg1, 0);
    *(u32 *) ((char *) arg1 + 0xa0c) = 2;
    func_0203edd0(arg1);
    *(u8 *) ((char *) arg0 + 0x1c) = 0;
    func_0201cbbc((char *) arg1 + 0x83c);

    if (arg1->v25() != 0) {
        func_0207d148((void *) arg1->v25());
    }
    return 1;
}
