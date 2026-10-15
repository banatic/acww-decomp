/* func_ov068_0226b260 @ 0x0226b260, 0xd0 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class GameObj {
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
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void *v25();
};

extern char data_021fbee8;
extern void *data_020c814c;

extern "C" {
u8 *func_020800d0(void *arg);
void func_ov068_0226cfd4(void *arg);
void func_ov068_02266c34(void *a0, void *a1, int a2, int a3, int a4, void *a5, int a6, void *a7, int a8);
void func_0204f794(void *arg, u8 b, int c);
void func_0201aff4(void *arg, int value);
void func_0202e194(void *arg);
void func_0201cbbc(void *arg);

int func_ov068_0226b260(void *a0, GameObj *thiz)
{
    u8 *p = func_020800d0(thiz->v25());

    func_ov068_0226cfd4(thiz);

    func_ov068_02266c34((char *) thiz + 0x898, thiz, 0, 0, 0, &data_021fbee8, 4, data_020c814c, 1);

    func_0204f794((char *) thiz + 0x5c, p[0], p[1] + 1);

    *(u16 *) ((char *) thiz + 0x8e) = 0;
    *(u16 *) ((char *) thiz + 0x94) = 0;

    func_0201aff4((char *) thiz + 0x350, 0);

    *(int *) ((char *) thiz + 0x64) += 0x1000;

    {
        int *src = (int *) ((char *) thiz + 0x5c);
        int *dst = (int *) ((char *) thiz + 0x68);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
    }

    func_0202e194(thiz);

    *(int *) ((char *) thiz + 0x4e8) |= 2;
    *(int *) ((char *) a0 + 0xf8) = -1;
    *((u8 *) thiz + 0x9f0) = 0;

    func_0201cbbc((char *) thiz + 0x83c);

    return 1;
}
}
