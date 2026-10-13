/* func_020153e0 @ 0x020153e0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_02068434(void *);

struct UnkStruct_020153e0 {
    char pad_00[0x40];
    void *unk_40;      // offset 0x40
    char pad_44[8];    // 0x44-0x4b
    char *unk_4C;      // offset 0x4c
    char pad_50[0x5c]; // 0x50-0xab
    char unk_AC;       // offset 0xac
};

int func_020153e0(struct UnkStruct_020153e0 *self)
{
    int result = 0;
    if (self->unk_4C != 0 && self->unk_40 != 0) {
        if (func_02019e00(self->unk_4C + 0x564) == 13) {
            if (func_02019de8(self->unk_4C + 0x564) != 0) {
                func_02068434(self->unk_40);
                self->unk_AC = 2;
                result = 1;
            }
        }
    }
    return result;
}
