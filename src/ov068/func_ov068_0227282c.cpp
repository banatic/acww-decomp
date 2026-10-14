/* func_ov068_0227282c @ 0x0227282c, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_0227282cEv
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" void func_ov009_02262ed4(void *, int);
extern "C" int func_02056f94(void *);
extern "C" void func_ov068_02272c64(void *);
extern "C" void func_02055124(void *);

void Obj_ov068_02277750::func_ov068_0227282c()
{
    void *p = (void *) this;
    func_ov009_02262ed4((void *) ((char *) p + 0x238), 0x888);
    if (func_02056f94((void *) ((char *) p + 0x1d8)) != 0) {
        ((Obj_ov068_02277750 *) p)->func_ov068_02272a7c(3);
    }
    func_ov068_02272c64(p);
    func_02055124((void *) ((char *) p + 0x13c));
}
