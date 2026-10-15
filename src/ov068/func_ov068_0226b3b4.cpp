/* func_ov068_0226b3b4 @ 0x0226b3b4, 0xd8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" void *func_0207f270(void *p);
extern "C" void *func_020800d0(void *p);
extern "C" int func_02019c6c(void *p, int a, unsigned short b);
extern "C" void func_ov068_02266c34(void *a, void *b, int c, int d, int e, void *f, int g, int h, int i);
extern "C" int func_02079544(void *p);
extern "C" void func_02079540(void *p, int b);
extern "C" void func_0202e194(void *p);
extern "C" void func_0204f794(void *p, unsigned char a, unsigned char b);
extern "C" void func_0201cbbc(void *p);

extern unsigned short data_020c80f8;
extern u32 data_020c814c;

struct Vec3 {
    int x;
    int y;
    int z;
};
struct Ret2 {
    unsigned char pad_00[0x1d];
    unsigned char unk_1D;
};

class UnkStruct_0226b3b4 {
  public:
    virtual void *vf0();
    virtual void *vf1();
    virtual void *vf2();
    virtual void *vf3();
    virtual void *vf4();
    virtual void *vf5();
    virtual void *vf6();
    virtual void *vf7();
    virtual void *vf8();
    virtual void *vf9();
    virtual void *vf10();
    virtual void *vf11();
    virtual void *vf12();
    virtual void *vf13();
    virtual void *vf14();
    virtual void *vf15();
    virtual void *vf16();
    virtual void *vf17();
    virtual void *vf18();
    virtual void *vf19();
    virtual void *vf20();
    virtual void *vf21();
    virtual void *vf22();
    virtual void *vf23();
    virtual void *vf24();
    virtual void *vf25();

    unsigned char pad_04[0x5c - 4];
    Vec3 src;
    Vec3 dst;
    unsigned char pad_74[0x562 - 0x74];
    unsigned char unk_562;
    unsigned char unk_563;
    unsigned char sub564;
    unsigned char pad_565[0x83c - 0x565];
    unsigned char sub83c;
    unsigned char pad_83D[0x898 - 0x83d];
    unsigned char sub898;
    unsigned char pad_899[0x9f0 - 0x899];
    unsigned char unk_9F0;
};

extern unsigned char data_021fbee8[];

extern "C" int func_ov068_0226b3b4(u32 unused, UnkStruct_0226b3b4 *obj)
{
    void *ret1 = obj->vf25();
    void *ret2 = func_0207f270(ret1);
    void *ret3 = func_020800d0(ret1);

    func_02019c6c(&obj->sub564, 1, data_020c80f8);
    func_ov068_02266c34(&obj->sub898, obj, 0, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);

    if (func_02079544(ret2) == 1) {
        func_02079540(ret2, 0);
    }

    ((Ret2 *) ret2)->unk_1D &= ~2;

    func_0202e194(obj);

    obj->unk_562 = 0;
    obj->unk_563 = 1;

    func_0204f794(&obj->src, ((u8 *) ret3)[0], ((u8 *) ret3)[1]);

    Vec3 *src = &obj->src;
    Vec3 *dst = &obj->dst;
    dst->x = obj->src.x;
    dst->y = src->y;
    dst->z = src->z;

    obj->unk_9F0 = 0;
    func_0201cbbc(&obj->sub83c);

    return 1;
}
