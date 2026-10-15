/* func_ov076_02278e78 @ 0x02278e78, 0x18 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_02278e78;

extern char data_ov076_02279744;
extern void *func_0202eb20(UnkStruct_02278e78 *);

UnkStruct_02278e78 *func_ov076_02278e78(UnkStruct_02278e78 *self)
{
    self->unk_00 = &data_ov076_02279744;
    func_0202eb20(self);
    return self;
}
