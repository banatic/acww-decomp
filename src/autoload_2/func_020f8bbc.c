/* func_020f8bbc @ 0x020f8bbc, 0x2b0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct NNSSndHandle {
    void *player;
} NNSSndHandle;

typedef struct UnkStruct_020f8bbc {
    u8 pad_00[4];
    int unk_04;
    NNSSndHandle handle;
    u8 pad_0C[1];
    u8 flag;
} UnkStruct_020f8bbc;

extern void NNS_SndPlayerSetTrackVolume(NNSSndHandle *handle, u16 trackBitMask, int volume);
extern void func_020eed18(int a, int b);
extern void func_020eedb8(int r0, int r1, int r2);
extern void ciAddUNQUIETFilter(void *a, int b);

void func_020f8bbc(UnkStruct_020f8bbc *self, int r1, int r2)
{
    if (r1 == 0) {
        NNS_SndPlayerSetTrackVolume(&self->handle, 1, 0x46);
        NNS_SndPlayerSetTrackVolume(&self->handle, 2, 0x50);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0xc, 0x78);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0x10, 0x6e);
        if (self->flag) {
            func_020eed18((int) &self->unk_04, 0);
            func_020eedb8(0x128, 1, (int) ((char *) self + 4));
        }
    } else if (r1 == 0x5a) {
        NNS_SndPlayerSetTrackVolume(&self->handle, 1, 0x4b);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0xe, 0x6e);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0x10, 0x6e);
        if (self->flag) {
            func_020eed18((int) &self->unk_04, 0);
            func_020eedb8(0x129, 1, (int) ((char *) self + 4));
        }
    } else if (r1 == 0xa0) {
        NNS_SndPlayerSetTrackVolume(&self->handle, 1, 0x50);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0xe, 0x6e);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0x10, 0x6e);
        if (self->flag) {
            func_020eed18((int) &self->unk_04, 0);
            func_020eedb8(0x12a, 1, (int) ((char *) self + 4));
        }
    } else if (r1 == 0x104) {
        NNS_SndPlayerSetTrackVolume(&self->handle, 1, 0x50);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0xe, 0x6e);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0x10, 0x64);
        if (self->flag) {
            func_020eed18((int) &self->unk_04, 0);
            func_020eedb8(0x12b, 1, (int) ((char *) self + 4));
        }
    } else if (r1 == 0x173) {
        NNS_SndPlayerSetTrackVolume(&self->handle, 1, 0x4b);
        NNS_SndPlayerSetTrackVolume(&self->handle, 2, 0);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0xc, 0x5a);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0x10, 0x4b);
        if (self->flag) {
            func_020eed18((int) &self->unk_04, 0);
            func_020eedb8(0x12c, 1, (int) ((char *) self + 4));
        }
    } else if (r1 == 0x1c3) {
        NNS_SndPlayerSetTrackVolume(&self->handle, 1, 0x55);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0xe, 0);
        NNS_SndPlayerSetTrackVolume(&self->handle, 0x10, 0x46);
        self->flag = ((self->flag + 1) % 2) != 0;
    }

    ciAddUNQUIETFilter(self, r2);
}
