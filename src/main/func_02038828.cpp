/* func_02038828 @ 0x02038828, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020382dc(void *);

#include "cpp/main/Base_02038828.h"

extern int data_021c593c;
extern Base_02038828::PMF data_020da4d8;
extern Base_02038828::PMF data_020da4e0;
extern Base_02038828::PMF data_020da4e8;
extern Base_02038828::PMF data_020da4f0;
extern Base_02038828::PMF data_020da4f8;
extern Base_02038828::PMF data_020da500;
extern Base_02038828::PMF data_020da508;
extern Base_02038828::PMF data_020da510;
extern Base_02038828::PMF data_021c5990[8];

extern "C" void func_02038828(Base_02038828 *self, unsigned char flag)
{
    self->unk_C9 = flag;
    func_020382dc(self);
    if (!(data_021c593c & 1)) {
        data_021c5990[0] = data_020da4e0;
        data_021c5990[1] = data_020da500;
        data_021c5990[2] = data_020da4d8;
        data_021c5990[3] = data_020da4e8;
        data_021c5990[4] = data_020da510;
        data_021c5990[5] = data_020da4f0;
        data_021c5990[6] = data_020da4f8;
        data_021c5990[7] = data_020da508;
        data_021c593c |= 1;
    }
    (self->*data_021c5990[self->unk_BC])();
}
