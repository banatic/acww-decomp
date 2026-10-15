/* func_ov003_0220c1e4 @ 0x0220c1e4, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223801019func_ov003_0220c1e4Ev
 */

#include "cpp/ov003/Obj_ov003_02238010.h"

extern "C" {
void func_ov003_0220c160(void);
void func_0203efb0(void *self, unsigned short value);
extern void *data_ov003_0223c5f4[];
extern unsigned char data_ov003_0223c5a0;
}

int Obj_ov003_02238010::func_ov003_0220c1e4()
{
    func_ov003_0220c160();
    func_0203efb0(this, (unsigned short) *(int *) (Base_0203f080::pad_04 + 4));
    func_ov003_0220c064(0);
    data_ov003_0223c5f4[*(int *) (Base_0203f080::pad_04 + 4)] = this;
    data_ov003_0223c5a0++;
    return 1;
}
