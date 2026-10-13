/* func_ov050_02261830 @ 0x02261830, 0xa0 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov050_02265b1419func_ov050_02261830Ei
 */

#include "cpp/ov050/Obj_ov050_02265b14.h"

typedef void (Obj_ov050_02265b14::*PMF)(int);

extern PMF data_ov050_02265570;
extern PMF data_ov050_02265700;
extern PMF data_ov050_02265560;

extern "C" int func_020984e8(void);
extern "C" void func_02099640(void);
extern "C" int func_02099020(int, int);

void Obj_ov050_02265b14::func_ov050_02261830(int param)
{
    static PMF table[3] = {data_ov050_02265570, data_ov050_02265700, data_ov050_02265560};
    int index;
    int a;
    int b;

    index = 0;
    a = func_020984e8();
    func_02099640();
    b = func_02099020(a, 1);
    if (b) {
        index = 2;
    } else if (unk_B0 == 15) {
        index = 1;
    }

    (this->*table[index])(param);
}
