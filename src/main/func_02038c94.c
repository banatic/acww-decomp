/* func_02038c94 @ 0x02038c94, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da560;
extern void *func_020a8c38(void *self);
extern void func_020edb3c(void *self);

struct UnkStruct_02038c94 {
    void *unk_00;
};

void *func_02038c94(void *self)
{
    ((struct UnkStruct_02038c94 *) self)->unk_00 = &data_020da560;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
