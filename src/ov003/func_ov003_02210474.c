/* func_ov003_02210474 @ 0x02210474, 0x90 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02210474 UnkStruct_02210474;
struct UnkStruct_02210474 {
    unsigned char pad_00[0x2d0];
    unsigned int unk_2D0[2];
    unsigned int unk_2D8;
    unsigned char pad_2DC[0x4f8];
    int unk_7D4;
    unsigned char pad_7D8[0x18];
    int unk_7F0;
    unsigned char pad_7F4[0x8];
    int unk_7FC;
    unsigned char pad_800[0xf0];
    unsigned int unk_8F0[4];
};

extern int func_02056f94(void *);
extern int func_02008258(UnkStruct_02210474 *, int);
extern void func_0200d4e8(UnkStruct_02210474 *, int, int, int);
extern void func_ov003_02210668(void *, int);
extern int func_ov003_0220d268(UnkStruct_02210474 *);
extern void func_0209129c(int, int);

void func_ov003_02210474(UnkStruct_02210474 *self)
{
    if (func_02056f94(self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8(self, 3, 1, -1);
    }

    {
        void *sub2 = self->unk_8F0;
        func_ov003_02210668(sub2, 0);
        if (((self->unk_2D8 << 4) >> 16) >= 0x21) {
            if (func_ov003_0220d268(self) != 0) {
                int *p = &self->unk_7D4;
                func_ov003_02210668(sub2, 1);
                if (self->unk_7D4 != -1) {
                    func_0209129c(self->unk_7D4, -1);
                    *p = -1;
                }
            }
        }
    }
}
