/* func_0201793c @ 0x0201793c, 0x178 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN12Obj_020d8bd413func_0201793cEi
 */

#include "cpp/main/Obj_020d8bd4.h"

extern int data_021c1534;
extern void (Obj_020d8bd4::*data_020d8644)(int);
extern void (Obj_020d8bd4::*data_020d865c)(int);
extern void (Obj_020d8bd4::*data_020d86dc)(int);
extern void (Obj_020d8bd4::*data_020d8854)(int);
extern void (Obj_020d8bd4::*data_020d885c)(int);
extern void (Obj_020d8bd4::*data_020d8864)(int);
extern void (Obj_020d8bd4::*data_020d886c)(int);
extern void (Obj_020d8bd4::*data_020d8874)(int);
extern void (Obj_020d8bd4::*data_020d887c)(int);
extern void (Obj_020d8bd4::*data_020d8884)(int);
extern void (Obj_020d8bd4::*data_020d888c)(int);
extern void (Obj_020d8bd4::*data_020d8894)(int);
extern void (Obj_020d8bd4::*data_020d889c)(int);
extern void (Obj_020d8bd4::*data_020d88a4)(int);
extern void (Obj_020d8bd4::*data_020d88ac)(int);
extern void (Obj_020d8bd4::*data_020d88bc)(int);
extern void (Obj_020d8bd4::*data_020d88d4)(int);
extern void (Obj_020d8bd4::*data_020d88dc)(int);
extern void (Obj_020d8bd4::*data_020d88e4)(int);
extern void (Obj_020d8bd4::*data_020d88ec)(int);
extern void (Obj_020d8bd4::*data_021c1874[20])(int);

void Obj_020d8bd4::func_0201793c(int p2)
{
    if (!(data_021c1534 & 1)) {
        data_021c1874[0] = data_020d88ec;
        data_021c1874[1] = data_020d88e4;
        data_021c1874[2] = data_020d88dc;
        data_021c1874[3] = data_020d88d4;
        data_021c1874[4] = data_020d8644;
        data_021c1874[5] = data_020d865c;
        data_021c1874[6] = data_020d88bc;
        data_021c1874[7] = data_020d86dc;
        data_021c1874[8] = data_020d88ac;
        data_021c1874[9] = data_020d88a4;
        data_021c1874[10] = data_020d889c;
        data_021c1874[11] = data_020d8894;
        data_021c1874[12] = data_020d888c;
        data_021c1874[13] = data_020d8884;
        data_021c1874[14] = data_020d887c;
        data_021c1874[15] = data_020d8874;
        data_021c1874[16] = data_020d886c;
        data_021c1874[17] = data_020d8864;
        data_021c1874[18] = data_020d885c;
        data_021c1874[19] = data_020d8854;
        data_021c1534 |= 1;
    }
    if (unk_98 < 20) {
        (this->*data_021c1874[unk_98])(p2);
    }
}
