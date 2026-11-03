/* pockets_swap_7: 2 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229e048 @ 0x0229e048, 0xa0 bytes, Thumb, emits _ZN18Obj_ov107_0229e3b819func_ov107_0229e048Ev
 * func_ov107_0229dea4 @ 0x0229dea4, 0x1a4 bytes, Thumb
 */

#include "cpp/ov107/Obj_ov107_0229e3b8.h"
#include "types.h"

extern "C" void func_ov107_0229dbb4(Obj_ov107_0229e3b8 *self);
extern "C" void func_ov107_0229db7c(Obj_ov107_0229e3b8 *self);

class UnkStruct_0229dea4 {
  public:
    u8 pad_00[0x8d];
    u8 idx; // offset 0x8d
};

typedef void (UnkStruct_0229dea4::*PMF)();

extern PMF data_ov107_0229e388;
extern PMF data_ov107_0229e300;
extern PMF data_ov107_0229e338;
extern PMF data_ov107_0229e370;
extern PMF data_ov107_0229e368;
extern PMF data_ov107_0229e360;
extern PMF data_ov107_0229e358;
extern PMF data_ov107_0229e350;
extern PMF data_ov107_0229e348;
extern PMF data_ov107_0229e340;
extern PMF data_ov107_0229e2d8;
extern PMF data_ov107_0229e330;
extern PMF data_ov107_0229e328;
extern PMF data_ov107_0229e320;
extern PMF data_ov107_0229e318;
extern PMF data_ov107_0229e310;
extern PMF data_ov107_0229e308;
extern PMF data_ov107_0229e2f8;
extern PMF data_ov107_0229e378;
extern PMF data_ov107_0229e2f0;
extern PMF data_ov107_0229e2e8;
extern PMF data_ov107_0229e2e0;
extern PMF data_ov107_0229e2a8;
extern PMF data_ov107_0229e2d0;

int Obj_ov107_0229e3b8::func_ov107_0229e048()
{
    static void (Obj_ov107_0229e3b8::*tbl[5])() = {
        &Obj_ov107_0229e3b8::func_ov107_0229de54, &Obj_ov107_0229e3b8::func_ov107_0229ddc4,
        &Obj_ov107_0229e3b8::func_ov107_0229dd88, &Obj_ov107_0229e3b8::func_ov107_0229dd28,
        &Obj_ov107_0229e3b8::func_ov107_0229dcdc};

    func_ov107_0229dbb4(this);
    (this->*tbl[state])();
    func_ov107_0229db7c(this);
    return 1;
}

extern "C" void func_ov107_0229dea4(UnkStruct_0229dea4 *obj)
{
    static struct {
        PMF a[16];
        PMF b[8];
    } gTables = {{data_ov107_0229e388, data_ov107_0229e300, data_ov107_0229e338, data_ov107_0229e370, data_ov107_0229e368,
                  data_ov107_0229e360, data_ov107_0229e358, data_ov107_0229e350, data_ov107_0229e348, data_ov107_0229e340,
                  data_ov107_0229e2d8, data_ov107_0229e330, data_ov107_0229e328, data_ov107_0229e320, data_ov107_0229e318,
                  data_ov107_0229e310},
                 {data_ov107_0229e308, data_ov107_0229e2f8, data_ov107_0229e378, data_ov107_0229e2f0, data_ov107_0229e2e8,
                  data_ov107_0229e2e0, data_ov107_0229e2a8, data_ov107_0229e2d0}};
    (obj->*gTables.a[obj->idx])();
}
