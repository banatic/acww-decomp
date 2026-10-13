/* func_ov082_02279044 @ 0x02279044, 0x20 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02279044 {
    void *unk_00;
} UnkStruct_02279044;

extern void func_0202eb20(UnkStruct_02279044 *);
extern void func_020edb3c(UnkStruct_02279044 *);
extern char data_ov082_0227978c;

UnkStruct_02279044 *func_ov082_02279044(UnkStruct_02279044 *self)
{
    self->unk_00 = (void *) &data_ov082_0227978c;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
