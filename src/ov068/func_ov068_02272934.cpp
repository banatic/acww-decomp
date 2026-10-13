/* func_ov068_02272934 @ 0x02272934, 0x148 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272934Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

typedef void (Obj_ov068_02277750::*PMF)();

extern PMF data_ov068_02278774[17];
extern int data_ov068_022786cc;

void Obj_ov068_02277750::func_ov068_02272934()
{
    if ((data_ov068_022786cc & 1) == 0) {
        data_ov068_02278774[0] = &Obj_ov068_02277750::func_ov068_022728fc;
        data_ov068_02278774[1] = &Obj_ov068_02277750::func_ov068_022728a8;
        data_ov068_02278774[2] = &Obj_ov068_02277750::func_ov068_0227282c;
        data_ov068_02278774[3] = &Obj_ov068_02277750::func_ov068_0227276c;
        data_ov068_02278774[4] = &Obj_ov068_02277750::func_ov068_022726c8;
        data_ov068_02278774[5] = &Obj_ov068_02277750::func_ov068_022726a0;
        data_ov068_02278774[6] = &Obj_ov068_02277750::func_ov068_02272550;
        data_ov068_02278774[7] = &Obj_ov068_02277750::func_ov068_02272530;
        data_ov068_02278774[8] = &Obj_ov068_02277750::func_ov068_022724b4;
        data_ov068_02278774[9] = &Obj_ov068_02277750::func_ov068_02272404;
        data_ov068_02278774[10] = &Obj_ov068_02277750::func_ov068_022723e0;
        data_ov068_02278774[11] = &Obj_ov068_02277750::func_ov068_02272338;
        data_ov068_02278774[12] = &Obj_ov068_02277750::func_ov068_0227227c;
        data_ov068_02278774[13] = &Obj_ov068_02277750::func_ov068_02272208;
        data_ov068_02278774[14] = &Obj_ov068_02277750::func_ov068_022721a0;
        data_ov068_02278774[15] = &Obj_ov068_02277750::func_ov068_02272114;
        data_ov068_02278774[16] = &Obj_ov068_02277750::func_ov068_022720b4;
        data_ov068_022786cc |= 1;
    }

    if (state_2b4 < 17) {
        (this->*data_ov068_02278774[state_2b4])();
    }
}
