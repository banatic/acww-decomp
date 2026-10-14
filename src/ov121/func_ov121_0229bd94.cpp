/* func_ov121_0229bd94 @ 0x0229bd94, 0x2a bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov121_0229c3a819func_ov121_0229bd94Ev
 */

#include "cpp/ov121/Obj_ov121_0229c3a8.h"

extern "C" int func_ov121_0229bcc8(void *);
extern "C" int func_ov121_0229b9e0(void *);
extern "C" int func_ov121_0229b9d8(void *);

int Obj_ov121_0229c3a8::func_ov121_0229bd94()
{
    void *p = (void *) this;
    if (func_ov121_0229bcc8(p)) {
        return 1;
    }
    func_ov121_0229b9e0(p);
    ((Obj_ov121_0229c3a8 *) p)->func_ov121_0229bdc0();
    func_ov121_0229b9d8(p);
    return 1;
}
