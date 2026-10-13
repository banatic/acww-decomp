/* func_ov004_02214474 @ 0x02214474, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov004/Obj_ov004_02252824.h"

extern "C" {
void func_ov004_0220d280(void *p, int a, int b);
int func_ov004_0220e4b0(void *p);
void func_02056ffc(void *p);
int func_02056f94(void *p);
}

extern "C" void func_ov004_02214474(Obj_ov004_02252824 *self)
{
    func_ov004_0220d280((char *) self + 0x740, 0, 0);
    if (func_ov004_0220e4b0((char *) self + 0x7c4) != 0) {
        func_02056ffc((char *) self + 0x7c4);
        **(int **) ((char *) self + 0x7dc) = *(int *) ((char *) self + 0x7cc);
        if (func_02056f94((char *) self + 0x7c4) != 0) {
            self->vfunc_70(0, 0xff);
        }
    } else {
        self->vfunc_70(0, 0xff);
    }
}
