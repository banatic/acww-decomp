/* func_ov068_022724b4 @ 0x022724b4, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_022724b4Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void *func_ov003_02220174(int a);
extern "C" int func_ov009_0226305c(void *argument0);
extern "C" void *func_ov009_02262fc0(void *p);
extern "C" void *func_ov009_02262fb4(void *p);

void Obj_ov068_02277750::func_ov068_022724b4()
{
    void *p = (void *) this;
    void *r4;
    void *r0;
    void *r1;
    void *r5 = p;
    r4 = func_ov003_02220174(0x5000);
    if (r4 != 0) {
        func_ov009_0226305c((void *) r4);
        r0 = func_ov009_02262fc0(r4);
        r1 = (void *) 0x2b8;
        *(void **) ((char *) r5 + (int) r1) = r0;
        r0 = func_ov009_02262fb4(r4);
        r1 = (void *) 0x2bc;
        *(void **) ((char *) r5 + (int) r1) = r0;
        ((Obj_ov068_02277750 *) r5)->func_ov068_02272a7c(9);
    }
}
