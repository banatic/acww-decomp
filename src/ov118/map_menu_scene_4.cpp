/* map_menu_scene_4: 2 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229c554 @ 0x0229c554, 0xe8 bytes, Thumb, emits _ZN18Obj_ov118_0229cc0819func_ov118_0229c554Ev
 * func_ov118_0229c528 @ 0x0229c528, 0x2a bytes, Thumb, emits _ZN18Obj_ov118_0229cc0819func_ov118_0229c528Ev
 */

#include "cpp/ov118/Obj_ov118_0229cc08.h"
#include "types.h"

extern "C" int func_ov118_0229c478(void *);
extern "C" void func_ov118_0229bf78(void *);
extern "C" void func_ov118_0229bf70(void *);

void Obj_ov118_0229cc08::func_ov118_0229c554()
{
    static void (Obj_ov118_0229cc08::*tbl[11])() = {
        &Obj_ov118_0229cc08::func_ov118_0229bd14, &Obj_ov118_0229cc08::func_ov118_0229bccc,
        &Obj_ov118_0229cc08::func_ov118_0229bc7c, &Obj_ov118_0229cc08::func_ov118_0229bb74,
        &Obj_ov118_0229cc08::func_ov118_0229bb48, &Obj_ov118_0229cc08::func_ov118_0229bb00,
        &Obj_ov118_0229cc08::func_ov118_0229babc, &Obj_ov118_0229cc08::func_ov118_0229ba98,
        &Obj_ov118_0229cc08::func_ov118_0229ba60, &Obj_ov118_0229cc08::func_ov118_0229ba34,
        &Obj_ov118_0229cc08::func_ov118_0229b8c8};
    (this->*tbl[subState])();
}

int Obj_ov118_0229cc08::func_ov118_0229c528()
{
    void *r0 = (void *) this;
    if (func_ov118_0229c478(r0)) {
        return 1;
    }
    func_ov118_0229bf78(r0);
    ((Obj_ov118_0229cc08 *) r0)->func_ov118_0229c554();
    func_ov118_0229bf70(r0);
    return 1;
}
