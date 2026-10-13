/* func_ov046_022608e4 @ 0x022608e4, 0x30 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xdc];
    int unk_DC;
} UnkStruct_022608e4;

extern int func_020b1558(void);
extern int func_ov046_022610fc(UnkStruct_022608e4 *self);

void func_ov046_022608e4(UnkStruct_022608e4 *self, int flag)
{
    if (flag == 0) {
        self->unk_DC = 7;
    } else {
        if (func_020b1558() < 16) {
            self->unk_DC = 42;
        } else {
            self->unk_DC = func_ov046_022610fc(self);
        }
    }
}
