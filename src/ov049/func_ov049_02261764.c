/* func_ov049_02261764 @ 0x02261764, 0x50 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b43c(void *a, int b);
extern void func_0206844c(void *a, void *b, int c);
extern int data_ov049_02263298;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x6C];
    void *unk_B0;
} UnkStruct_02261764;

void func_ov049_02261764(UnkStruct_02261764 *self, int cond)
{
    char buffer[8];
    if (cond != 0) {
        return;
    }
    if (func_0201b43c(self->unk_B0, 0x15e) == 0) {
        buffer[0] = 0xd;
        func_0206844c(self->unk_40, buffer, data_ov049_02263298);
    } else {
        buffer[1] = 0xe;
        func_0206844c(self->unk_40, &buffer[1], data_ov049_02263298);
    }
}
