/* func_02070798 @ 0x02070798, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02070798 {
    void *unk_00;
};

extern void *data_020e1784[];
void *func_020a887c(struct UnkStruct_02070798 *self);
void func_020edb3c(struct UnkStruct_02070798 *self);

struct UnkStruct_02070798 *func_02070798(struct UnkStruct_02070798 *self)
{
    self->unk_00 = data_020e1784;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}
