/* func_ov003_0221648c @ 0x0221648c, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern int func_02008dc0(void *, short, int, int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_02073908(void *, int);
extern int func_ov003_0220d268(void *);
extern void *data_020ccf94;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x240];
    char unk_2D0[8];
    unsigned int unk_2D8;
    char pad_2DC[0x4fb];
    unsigned char unk_7D7;
    char pad_7D8[0x18];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
    int unk_800;
} UnkStruct_0221648c;

void func_ov003_0221648c(UnkStruct_0221648c *self)
{
    unsigned char flag = self->unk_7D7;
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        if (flag != 0) {
            func_02008dc0(self, self->unk_8E, 6, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
    if (flag != 0) {
        return;
    }
    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        return;
    }
    if (((self->unk_2D8 << 4) >> 16) > 8) {
        func_ov003_0220d268(self);
    }
}
