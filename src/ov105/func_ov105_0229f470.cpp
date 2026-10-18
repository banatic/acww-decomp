/* func_ov105_0229f470 @ 0x0229f470, 0x194 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

class PmfBase;
typedef void (PmfBase::*PMF)();

// The state handlers: member-function pointer constants the ROM keeps in .data.
extern PMF data_ov105_0229f9a0, data_ov105_0229f898, data_ov105_0229f9d8, data_ov105_0229fa38, data_ov105_0229fa30,
    data_ov105_0229fa28, data_ov105_0229fa20, data_ov105_0229fa18, data_ov105_0229fa10, data_ov105_0229fa08,
    data_ov105_0229fa00, data_ov105_0229f9f8, data_ov105_0229f9f0, data_ov105_0229f9e8, data_ov105_0229f9e0,
    data_ov105_0229f918, data_ov105_0229f9d0, data_ov105_0229f9c8, data_ov105_0229f9c0, data_ov105_0229f9b8,
    data_ov105_0229f9b0, data_ov105_0229f9a8;

extern "C" void func_ov105_0229eaa4(void *self);
extern "C" void func_ov105_0229ea6c(void *self);

struct UnkStruct_0229f470 {
    char pad_00[0x8c];
    unsigned char idx;
};

extern "C" int func_ov105_0229f470(UnkStruct_0229f470 *self)
{
    static PMF tbl[22] = {data_ov105_0229f9a0, data_ov105_0229f898, data_ov105_0229f9d8, data_ov105_0229fa38,
                          data_ov105_0229fa30, data_ov105_0229fa28, data_ov105_0229fa20, data_ov105_0229fa18,
                          data_ov105_0229fa10, data_ov105_0229fa08, data_ov105_0229fa00, data_ov105_0229f9f8,
                          data_ov105_0229f9f0, data_ov105_0229f9e8, data_ov105_0229f9e0, data_ov105_0229f918,
                          data_ov105_0229f9d0, data_ov105_0229f9c8, data_ov105_0229f9c0, data_ov105_0229f9b8,
                          data_ov105_0229f9b0, data_ov105_0229f9a8};

    func_ov105_0229eaa4(self);
    (((PmfBase *) self)->*tbl[self->idx])();
    func_ov105_0229ea6c(self);
    return 1;
}
