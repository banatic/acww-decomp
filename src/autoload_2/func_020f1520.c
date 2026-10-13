/* func_020f1520 @ 0x020f1520, 0xfc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct UnkStruct_020f1520_2 {
    u8 pad_00[2];
    u16 flag;
};

typedef struct {
    u32 unk_00;
    struct UnkStruct_020f1520_2 sub;
    u8 pad_08[0x2c - 0x8];
    void *ptr;
    u8 pad_30[0x3c - 0x30];
    u8 sound[0x64 - 0x3c];
    u16 unk_64;
    u8 pad_66[0x6c - 0x66];
    s16 unk_6C;
    u16 unk_6E;
} UnkStruct_020f1520;

extern int func_020f0d50(void *sub);
extern void func_020f0ddc(void *sub, int a);
extern void func_020f0d98(void *sub, int a, int b);
extern void NNS_SndPlayerSetTrackVolume(void *player, int track, int volume);

void func_020f1520(UnkStruct_020f1520 *self)
{
    void *ptr;
    signed char c;
    s16 s;
    int vol;

    ptr = self->ptr;
    if (ptr == 0) {
        return;
    }
    c = *(signed char *) ((u8 *) ptr + 4);

    if (c >= 0x28 && c < 0x32) {
        if (self->sub.flag != 0) {
            vol = func_020f0d50(&self->sub);
            NNS_SndPlayerSetTrackVolume(self->sound, self->unk_64, vol);
        }
    }

    if (c == 1 || c == 3) {
        s = self->unk_6C;
        if (s > 0) {
            self->unk_6C = s - 1;
        } else if (s == 0) {
            func_020f0ddc(&self->sub, 0);
            func_020f0d98(&self->sub, 0x7f, 0x258);
            self->unk_6C = -1;
        }
        if (self->sub.flag == 0) {
            return;
        }
        vol = func_020f0d50(&self->sub);
        NNS_SndPlayerSetTrackVolume(self->sound, self->unk_64, vol);
        NNS_SndPlayerSetTrackVolume(self->sound, self->unk_6E, 0x7f - vol);
    }
}
