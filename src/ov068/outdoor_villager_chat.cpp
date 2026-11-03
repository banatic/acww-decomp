/* outdoor_villager_chat: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02269ae4 @ 0x02269ae4, 0x52 bytes, Thumb
 * func_ov068_02269a54 @ 0x02269a54, 0x90 bytes, Thumb
 */

#include "cpp/main/Obj_020d9e88.h"

// partner object at 0x644 and its flag at 0x648
extern "C" Obj_020d9e88 *func_0201ce50(Obj_020d9e88 *obj);
extern "C" void func_0201ce5c(Obj_020d9e88 *obj, Obj_020d9e88 *partner);
extern "C" void func_0201ce44(Obj_020d9e88 *obj, unsigned char flag);
extern "C" int func_ov068_0226ccb0(void *, Obj_020d9e88 *);
extern "C" void func_ov068_0226cce8(void *, Obj_020d9e88 *, int);
extern "C" void func_ov068_0226cbf4(void *);

class UnkStruct_02269a54 {
  public:
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    int method(int arg);
};

typedef int (UnkStruct_02269a54::*PMF)(int);

extern PMF data_ov068_02277048;
extern PMF data_ov068_02277060;
extern PMF data_ov068_02277068;
extern PMF data_ov068_02277078;

extern "C" void func_ov068_02269ae4(void *arg0, Obj_020d9e88 *obj)
{
    Obj_020d9e88 *partner = func_0201ce50(obj);
    if (partner != 0) {
        if (partner->vfunc_bc()) {
            func_0201ce5c(obj, 0);
            func_0201ce44(obj, 0);
            if (func_ov068_0226ccb0(arg0, obj) == 0) {
                func_ov068_0226cce8(arg0, obj, 0);
            }
            func_ov068_0226cbf4(arg0);
        }
    }
}

extern "C" int func_ov068_02269a54(UnkStruct_02269a54 *p, int arg)
{
    static PMF table[4];
    static int init_done = 0;
    if (!(init_done & 1)) {
        table[0] = data_ov068_02277048;
        table[1] = data_ov068_02277060;
        table[2] = data_ov068_02277068;
        table[3] = data_ov068_02277078;
        init_done |= 1;
    }
    unsigned char index = p->unk_1C;
    if (index < 4) {
        (p->*table[index])(arg);
    }
    return 0;
}
