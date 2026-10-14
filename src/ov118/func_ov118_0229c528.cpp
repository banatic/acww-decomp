/* func_ov118_0229c528 @ 0x0229c528, 0x2a bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov118_0229cc0819func_ov118_0229c528Ev
 */

#include "cpp/ov118/Obj_ov118_0229cc08.h"

extern "C" int func_ov118_0229c478(void *);
extern "C" int func_ov118_0229bf78(void *);
extern "C" int func_ov118_0229bf70(void *);

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
