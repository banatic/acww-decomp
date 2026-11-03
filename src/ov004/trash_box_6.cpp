/* trash_box_6: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f994 @ 0x0222f994, 0xa8 bytes, Thumb
 * func_ov004_0222f908 @ 0x0222f908, 0x8c bytes, Thumb, emits _ZN18Obj_ov004_022553d819func_ov004_0222f908Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_022553d8.h"

struct UnkStruct_0222f994;

typedef int (UnkStruct_0222f994::*PMF)(void);

struct UnkStruct_0222f994 {
    u8 pad_00[0x24c];
    u8 unk_24C;
};

extern PMF data_ov004_02255380;
extern PMF data_ov004_02255378;
extern PMF data_ov004_02255370;
extern PMF data_ov004_02255368;
extern "C" int func_ov004_0222c558(UnkStruct_0222f994 *self, unsigned int i);

typedef void (Obj_ov004_022553d8::*Pmf)(void);

extern "C" int func_ov004_0222f994(UnkStruct_0222f994 *self, unsigned int i)
{
    static PMF tbl[4] = {data_ov004_02255380, data_ov004_02255378, data_ov004_02255370, data_ov004_02255368};

    if (i < 4) {
        if ((self->*tbl[i])() != 0) {
            if (func_ov004_0222c558(self, i) != 0) {
                self->unk_24C = i;
                return 1;
            }
        }
    }
    return 0;
}

void Obj_ov004_022553d8::func_ov004_0222f908()
{
    static Pmf tbl[] = {&Obj_ov004_022553d8::func_ov004_0222f8cc, &Obj_ov004_022553d8::func_ov004_0222f854,
                        &Obj_ov004_022553d8::func_ov004_0222f818, &Obj_ov004_022553d8::func_ov004_0222f7a0};
    unsigned char i = unk_24c;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
