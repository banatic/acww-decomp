/* func_020650ac @ 0x020650ac, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} LocalData;

typedef struct {
    u32 pad_00[3];
    u32 unk_0C;
    unsigned char pad_10[0x24];
    u16 unk_34;
    u16 pad_36;
    LocalData sub;
} UnkStruct_020650ac;

extern int data_021c67a4;
extern void func_02065110(UnkStruct_020650ac *obj, LocalData *data);
extern int func_0203c590(int value);
extern void func_020ea78c(LocalData *data, int value);
extern int func_020bbf00(int value);
extern void func_0206515c(LocalData *src, LocalData *dst);

void func_020650ac(UnkStruct_020650ac *obj)
{
    volatile u16 t1, t2;
    LocalData local1;
    LocalData local2;
    LocalData *dst;
    int ret;

    local1.a = 0;
    local1.b = 0;
    local1.c = 0xfffff000;

    func_02065110(obj, &local1);

    if (data_021c67a4) {
        ret = func_0203c590(data_021c67a4);
        func_020ea78c(&local1, ret);
    }

    t1 = (u16) func_020bbf00(obj->unk_0C);
    t2 = t1;
    obj->unk_34 = t2;

    local2.a = local1.a;
    local2.b = local1.b;
    local2.c = local1.c;

    dst = &obj->sub;
    func_0206515c(&local2, dst);
}
