/* func_ov073_02278f98 @ 0x02278f98, 0x44 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02278f98 {
    char pad_00[0xB8];
    void (UnkStruct_02278f98::*pmf)();
};

extern void (UnkStruct_02278f98::*data_0213dd98)();

extern "C" void func_ov073_02278f98(UnkStruct_02278f98 *self)
{
    if (self->pmf == 0) {
        return;
    }
    (self->*self->pmf)();
    self->pmf = data_0213dd98;
}
