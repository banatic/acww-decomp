/* func_0208d72c @ 0x0208d72c, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e226c.h"

extern "C" {
int func_020b45d0(Obj_020e21e4 *, unsigned char, int, int, int, int);
void func_02051624(void *);
void func_02051694(void *);
}

struct Other {
    unsigned char pad_00[0x10];
    int unk_10;
};

extern "C" void func_0208d72c(Obj_020e226c *self)
{
    if (self->unk_28 == 0) {
        return;
    }
    if (self->unk_48 == 0) {
        return;
    }
    self->unk_48 = 0;
    func_020b45d0(&self->unk_68[0], self->unk_61, 2, 0, 0, 1);
    Other *ptr = (Other *) self->unk_28;
    ptr->unk_10 = self->unk_68[0].vfunc_0c();
    func_02051624(self->unk_28);
    func_02051694(self->unk_28);
}
