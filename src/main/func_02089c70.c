/* func_02089c70 @ 0x02089c70, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a07c(void *self);
extern int data_020e2008;

struct UnkStruct_02089c70 {
    void *unk_00;
};

struct UnkStruct_02089c70 *func_02089c70(struct UnkStruct_02089c70 *self)
{
    self->unk_00 = &data_020e2008;
    func_0208a07c(self);
    return self;
}
