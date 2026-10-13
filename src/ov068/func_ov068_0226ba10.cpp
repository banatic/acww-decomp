/* func_ov068_0226ba10 @ 0x0226ba10, 0x12c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {

int func_ov068_0226ca74(void *, void *);
void func_ov068_0226cce8(void *, void *, int);
void func_0202c57c(void *, void *, void *, int);
void func_ov068_0226d01c(void *);
void func_0207d1f8(int, int);
int func_02013894(void *);
void func_ov068_0226c964(void *, int, void *);
int func_ov068_0226c8b0(void *, void *);
int func_02013300(void *);
int func_ov068_0226c910(void *, void *);
void func_02013948(void *, void *, int, int, void *);
int func_020132a0(void *, void *);

extern char data_ov068_0227677c;
extern char data_ov068_02276734;
}

class UnkStruct_0226ba10 {
  public:
    virtual void *v00();
    virtual void *v01();
    virtual void *v02();
    virtual void *v03();
    virtual void *v04();
    virtual void *v05();
    virtual void *v06();
    virtual void *v07();
    virtual void *v08();
    virtual void *v09();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual int vfunc(); // vtable offset 0x64

    char pad_04[0x58]; // offsets 0x4..0x5b
    char sub5c;        // offset 0x5c
};

struct SomeA {
    u8 pad_00[0x3c];
    char sub3c;      // 0x3c
    u8 pad_3D[0x9b]; // 0x3c+0x9b = 0xd7
    short d8;        // 0xd8
    short da;        // 0xda
    u8 pad_DC[0x1c]; // 0xdc..0xf7
    int unk_F8;      // 0xf8
};

extern "C" int func_ov068_0226ba10(SomeA *a, UnkStruct_0226ba10 *b)
{
    if (func_ov068_0226ca74(a, b)) {
        func_ov068_0226cce8(a, b, 0);
        goto exit;
    }

    func_0202c57c(b, &data_ov068_0227677c, &data_ov068_02276734, 1);
    func_ov068_0226d01c(b);

    if (a->unk_F8 == 0) {
        if (b->vfunc() != 0) {
            func_0207d1f8(b->vfunc(), 0);
        }
        a->unk_F8 = 0x384;
    }

    if (func_02013894(&a->sub3c) && a->d8) {
        // nothing
    } else {
        func_ov068_0226c964(a, 1, b);
        a->d8 = -1;
        a->da = 0;
    }

    if (func_02013894(&a->sub3c) == 0) {
        goto exit;
    }

    if (func_ov068_0226c8b0(a, b)) {
        func_ov068_0226cce8(a, b, 3);
        goto exit;
    }

    if (func_02013300(&a->sub3c) == 3) {
        goto skip;
    }
    if (func_ov068_0226c910(a, b)) {
        func_02013948(&a->sub3c, &b->sub5c, 3, 1, b);
        a->da = 0;
    }
skip:
    if (a->da != 0) {
        goto exit;
    }
    if (func_020132a0(&a->sub3c, &b->sub5c)) {
        if (a->d8 == -1) {
            a->d8 = 0x1770;
        }
    }
    a->da = 0x28;

exit:
    return 1;
}
