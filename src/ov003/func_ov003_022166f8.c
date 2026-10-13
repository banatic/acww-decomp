/* func_ov003_022166f8 @ 0x022166f8, 0x46 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022166f8 {
    char pad_00[0x98];
    int unk_98;
};
extern void func_ov003_02216948(struct UnkStruct_022166f8 *self);
extern void func_0201100c(struct UnkStruct_022166f8 *self);
extern void func_02010d64(struct UnkStruct_022166f8 *self);
extern int func_02011398(int a, int b);
extern void func_0201107c(struct UnkStruct_022166f8 *self, int *out);
extern void func_ov003_02216740(struct UnkStruct_022166f8 *self);

void func_ov003_022166f8(struct UnkStruct_022166f8 *self)
{
    int val;
    int temp;
    func_ov003_02216948(self);
    func_0201100c(self);
    func_02010d64(self);
    val = self->unk_98;
    if (val < 0) {
        val = -val;
    }
    temp = -1 * func_02011398(val, 0);
    func_0201107c(self, &temp);
    func_ov003_02216740(self);
}
