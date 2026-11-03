/* design_editor_10: 3 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229c650 @ 0x0229c650, 0x104 bytes, Thumb
 * func_ov123_0229c54c @ 0x0229c54c, 0x104 bytes, Thumb, emits _ZN18Obj_ov123_0229d02419func_ov123_0229c54cEv
 * func_ov123_0229c530 @ 0x0229c530, 0x1c bytes, Thumb, emits _ZN18Obj_ov123_0229d02419func_ov123_0229c530Ev
 */

#include "cpp/ov123/Obj_ov123_0229d024.h"

struct UnkStruct_0229c650;

typedef void (UnkStruct_0229c650::*PMF)();

extern PMF data_ov123_0229ce70;
extern PMF data_ov123_0229ce80;
extern PMF data_ov123_0229ced8;
extern PMF data_ov123_0229ce48;
extern PMF data_ov123_0229ce58;
extern PMF data_ov123_0229cf38;
extern PMF data_ov123_0229cec0;
extern PMF data_ov123_0229ce40;
extern PMF data_ov123_0229cf58;
extern PMF data_ov123_0229cf50;
extern PMF data_ov123_0229cf48;
extern PMF data_ov123_0229cf40;

struct UnkStruct_0229c650 {
    char pad_00[0x8c];
    unsigned char index;
};

extern "C" void func_ov123_0229bf64(UnkStruct_0229c650 *self);
extern "C" void func_ov123_0229bf50(UnkStruct_0229c650 *self);

typedef void (Obj_ov123_0229d024::*Handler)();

extern "C" void func_ov123_0229bf90(void *);
extern "C" void func_ov123_0229bf88(void *);

extern "C" int func_ov123_0229c650(UnkStruct_0229c650 *self)
{
    static PMF pmf_table[12] = {data_ov123_0229ce70, data_ov123_0229ce80, data_ov123_0229ced8, data_ov123_0229ce48,
                                data_ov123_0229ce58, data_ov123_0229cf38, data_ov123_0229cec0, data_ov123_0229ce40,
                                data_ov123_0229cf58, data_ov123_0229cf50, data_ov123_0229cf48, data_ov123_0229cf40};
    func_ov123_0229bf64(self);
    (self->*pmf_table[self->index])();
    func_ov123_0229bf50(self);
    return 1;
}

void Obj_ov123_0229d024::func_ov123_0229c54c()
{
    static Handler table[] = {&Obj_ov123_0229d024::func_ov123_0229bd9c, &Obj_ov123_0229d024::func_ov123_0229bd20,
                              &Obj_ov123_0229d024::func_ov123_0229bc70, &Obj_ov123_0229d024::func_ov123_0229bb74,
                              &Obj_ov123_0229d024::func_ov123_0229baa4, &Obj_ov123_0229d024::func_ov123_0229b9bc,
                              &Obj_ov123_0229d024::func_ov123_0229b8ec, &Obj_ov123_0229d024::func_ov123_0229b89c,
                              &Obj_ov123_0229d024::func_ov123_0229b7e4, &Obj_ov123_0229d024::func_ov123_0229b7b8,
                              &Obj_ov123_0229d024::func_ov123_0229b77c, &Obj_ov123_0229d024::func_ov123_0229b754,
                              &Obj_ov123_0229d024::func_ov123_0229b6e8};
    (this->*table[subState])();
}

int Obj_ov123_0229d024::func_ov123_0229c530()
{
    void *a = (void *) this;
    func_ov123_0229bf90(a);
    ((Obj_ov123_0229d024 *) a)->func_ov123_0229c54c();
    func_ov123_0229bf88(a);
    return 1;
}
