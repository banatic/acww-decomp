/* func_0206da00 @ 0x0206da00, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020df228;
extern void *func_020a8c38(void *a);
extern void func_020edb3c(void *a);

struct UnkStruct_0206da00 {
    int *unk_00;
};

void *func_0206da00(struct UnkStruct_0206da00 *self)
{
    self->unk_00 = &data_020df228;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
