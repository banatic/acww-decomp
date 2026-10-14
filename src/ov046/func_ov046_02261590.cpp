/* func_ov046_02261590 @ 0x02261590, 0x44 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261590 {
    char pad_00[0xB8];
    void (UnkStruct_02261590::*pmf)();
};
extern void (UnkStruct_02261590::*__ptmf_null)();
extern "C" void func_ov046_02261590(UnkStruct_02261590 *self)
{
    if (self->pmf != 0) {
        (self->*self->pmf)();
        self->pmf = __ptmf_null;
    }
}
