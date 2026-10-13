/* func_ov003_02218960 @ 0x02218960, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern unsigned int func_02008258(void *, unsigned int);
extern void func_0200d4e8(void *, int, int, int);
extern int func_02073908(void *, unsigned int);
extern void func_ov003_0220d268(void *);
extern void func_0200f268(void *, int);
extern void *data_020ccf94;

typedef struct {
    char pad_00[0x2d0];
    char unk_2D0[8];
    unsigned int unk_2D8;
    char pad_2DC[0x514];
    unsigned int unk_7F0;
    char pad_7F4[0x8];
    unsigned int unk_7FC;
    unsigned int unk_800;
} UnkStruct_02218960;

void func_ov003_02218960(UnkStruct_02218960 *self)
{
    if (func_02056f94(self->unk_2D0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }
    if (((self->unk_2D8 << 4) >> 16) >= 0xe) {
        if (func_02073908(data_020ccf94, self->unk_800)) {
            func_ov003_0220d268(self);
        } else {
            func_0200f268(self, 0x12);
        }
    }
}
