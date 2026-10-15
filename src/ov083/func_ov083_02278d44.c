/* func_ov083_02278d44 @ 0x02278d44, 0x20 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278d44 {
    void *unk_00;
} UnkStruct_02278d44;

extern int data_ov083_022791fc;
extern void *func_0202eb20(UnkStruct_02278d44 *self);
extern void func_020edb3c(UnkStruct_02278d44 *self);

UnkStruct_02278d44 *func_ov083_02278d44(UnkStruct_02278d44 *self)
{
    self->unk_00 = &data_ov083_022791fc;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
