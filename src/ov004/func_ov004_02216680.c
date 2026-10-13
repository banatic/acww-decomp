/* func_ov004_02216680 @ 0x02216680, 0x12 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02216680 UnkStruct_02216680;
struct UnkStruct_02216680 {
    void (**vt)(UnkStruct_02216680 *);
};
void func_ov004_02216680(UnkStruct_02216680 *self)
{
    self->vt[32](self);
}
