/* func_ov134_0229a868 @ 0x0229a868, 0x38 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229a96c(void *self, int value, int kind);

typedef struct {
    char pad_00[0xb1];
    unsigned char b;
} UnkStruct_0229a868;

void func_ov134_0229a868(UnkStruct_0229a868 *self, int arg1)
{
    unsigned char old = self->b;
    if (old == arg1) {
        return;
    }
    self->b = arg1;
    if (old != 6) {
        func_ov134_0229a96c(self, old, 3);
    }
    if (arg1 != 6) {
        func_ov134_0229a96c(self, arg1, 3);
    }
}
