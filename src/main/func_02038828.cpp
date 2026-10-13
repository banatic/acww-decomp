/* func_02038828 @ 0x02038828, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020382dc(void *);

#include "cpp/main/Base_02038828.h"

extern "C" void func_02038828(Base_02038828 *self, unsigned char flag)
{
    self->unk_C9 = flag;
    func_020382dc(self);
    static Base_02038828::PMF s_table[8] = {
        &Base_02038828::func_020382d0, &Base_02038828::func_0203827c, &Base_02038828::func_0203822c,
        &Base_02038828::func_020381d8, &Base_02038828::func_020380f4, &Base_02038828::func_020380a8,
        &Base_02038828::func_02037fe8, &Base_02038828::func_02037fa8,
    };
    (self->*s_table[self->unk_BC])();
}
