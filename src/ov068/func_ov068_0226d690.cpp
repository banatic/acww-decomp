/* func_ov068_0226d690 @ 0x0226d690, 0x98 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define IN(v, lo, hi) ((v) >= (lo) && (v) <= (hi))

class UnkStruct_0226d690 {
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
    virtual void *v25();
    char pad_04[0x830 - 4];
    int unk_830;
    char pad_834[0x9f4 - 0x834];
    int unk_9F4;
    char pad_9F8[0xa05 - 0x9f8];
    u8 unk_A05;
};

extern "C" void func_0207d148(void *);
extern "C" int func_0207dd84(int);
extern "C" void func_ov068_02266e80(int *, UnkStruct_0226d690 *);
extern "C" void func_ov068_02266e78(int *, unsigned short);
extern "C" int func_ov068_0226d598(UnkStruct_0226d690 *);
extern unsigned short data_ov068_0227672c;

extern "C" int func_ov068_0226d690(UnkStruct_0226d690 *self, unsigned short *pw)
{
    int r;
    unsigned int t;
    unsigned short w;

    r = 0;
    t = 0;
    w = *pw;
    if (w >= 0x1376 && w <= 0x1376) {
        t = 1;
    }
    if (t > 0 || IN(w, 0x1377, 0x1377)) {
        if (self->v25() != 0) {
            func_0207d148(self->v25());
        }
        if (func_0207dd84(self->unk_830) != 0) {
            func_ov068_02266e80(&self->unk_9F4, self);
            func_ov068_02266e78(&self->unk_9F4, data_ov068_0227672c);
            r = 1;
        } else {
            if (func_ov068_0226d598(self) != 0) {
                self->unk_A05 = 1;
            }
        }
    }
    return r;
}
