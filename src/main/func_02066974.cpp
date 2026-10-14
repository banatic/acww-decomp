/* func_02066974 @ 0x02066974, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN13Base_0206699417vfunc_02066994_08Ev
 */

#include "cpp/main/Base_02066994.h"

extern "C" {
void func_020a8170(void *param1);
void func_020a8c1c(void *param2);
}

// Slot 0x08 of the receiver vtable: reset the receiver.
void Base_02066994::vfunc_02066994_08()
{
    func_020a8170(this);
    func_020a8c1c((char *) this + 0x20);
    unk_40 = 0;
    *((char *) this + 0x44) = 0;
}
