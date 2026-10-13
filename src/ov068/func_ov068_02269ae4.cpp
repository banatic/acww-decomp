/* func_ov068_02269ae4 @ 0x02269ae4, 0x52 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d9e88.h"

// partner object at 0x644 and its flag at 0x648
extern "C" Obj_020d9e88 *func_0201ce50(Obj_020d9e88 *obj);
extern "C" void func_0201ce5c(Obj_020d9e88 *obj, Obj_020d9e88 *partner);
extern "C" void func_0201ce44(Obj_020d9e88 *obj, unsigned char flag);
extern "C" int func_ov068_0226ccb0(void *, Obj_020d9e88 *);
extern "C" void func_ov068_0226cce8(void *, Obj_020d9e88 *, int);
extern "C" void func_ov068_0226cbf4(void *);

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
