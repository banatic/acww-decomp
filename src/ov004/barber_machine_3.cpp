/* barber_machine_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222cc24 @ 0x0222cc24, 0x1c bytes, Thumb
 * func_ov004_0222cb88 @ 0x0222cb88, 0x9c bytes, Thumb
 */

#include "cpp/ov004/Obj_ov004_02254c58.h"

struct V {
    int x, y, z;
    ~V() {}
};

typedef int (Obj_ov004_02254c58::*Pmf)(void);

// Unused local of a class with a destructor; it only reserves stack space.
extern "C" void func_ov004_0222cc24(void *self, V *out)
{
    V t;

    out->x = 0xc000;
    out->y = 0;
    out->z = 0x17000;
}

extern "C" int func_ov004_0222cb88(Obj_ov004_02254c58 *self, unsigned int i)
{
    {
        static Pmf tbl[] = {&Obj_ov004_02254c58::func_ov004_0222cac4, &Obj_ov004_02254c58::func_ov004_0222ca78,
                            &Obj_ov004_02254c58::func_ov004_0222c9fc, &Obj_ov004_02254c58::func_ov004_0222c964};
        if (i < 4) {
            if ((self->*(tbl[i]))()) {
                self->unk_24c = (unsigned char) i;
                return 1;
            }
        }
    }
    return 0;
}
