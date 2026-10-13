/* func_ov109_0229d8e0 @ 0x0229d8e0, 0xa0 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229d8e0 {
    virtual void f() {}
    u8 pad[0x88];
    u8 idx;
};

typedef void (UnkStruct_0229d8e0::*PMF)();

extern PMF data_ov109_0229dba8;
extern PMF data_ov109_0229dbc8;
extern PMF data_ov109_0229dbc0;
extern PMF data_ov109_0229dbb8;
extern PMF data_ov109_0229dbb0;

extern "C" void func_ov109_0229d478(UnkStruct_0229d8e0 *);
extern "C" void func_ov109_0229d440(UnkStruct_0229d8e0 *);

extern "C" int func_ov109_0229d8e0(UnkStruct_0229d8e0 *self)
{
    static PMF tbl[5] = {data_ov109_0229dba8, data_ov109_0229dbc8, data_ov109_0229dbc0, data_ov109_0229dbb8,
                         data_ov109_0229dbb0};
    func_ov109_0229d478(self);
    (self->*tbl[self->idx])();
    func_ov109_0229d440(self);
    return 1;
}
