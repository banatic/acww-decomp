/* func_ov003_022173e0 @ 0x022173e0, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209129c(int value);

typedef struct {
    char pad_00[0x7D8];
    int unk_7D8;
} UnkStruct_022173e0;

void func_ov003_022173e0(UnkStruct_022173e0 *self)
{
    if (self->unk_7D8 != -1) {
        func_0209129c(self->unk_7D8);
    }
}
