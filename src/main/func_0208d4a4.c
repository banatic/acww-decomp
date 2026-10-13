/* func_0208d4a4 @ 0x0208d4a4, 0xba bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    u16 w;
    u8 b[2];
} U16;

extern void func_0209df94(void *);
extern void func_0209def4(void *);
extern u32 MB_GetBeaconRecvStatus(void);

typedef struct {
    u8 pad_00[0x48];
    u8 flags[6];
    u8 pad_4E[0x12];
    U16 unk_60;
    U16 unk_62;
    u32 unk_64;
} UnkStruct_0208d4a4;

void func_0208d4a4(UnkStruct_0208d4a4 *self)
{
    U16 v[2];
    u32 s;

    func_0209df94(&v[0]);
    func_0209def4(&v[1]);
    s = MB_GetBeaconRecvStatus();

    if (v[0].w != self->unk_60.w) {
        if (v[0].b[1] != self->unk_60.b[1]) {
            self->flags[0] = 1;
        }
        if (v[0].b[0] != self->unk_60.b[0]) {
            self->flags[1] = 1;
        }
        self->unk_60.w = v[0].w;
    }

    if (v[1].w != self->unk_62.w) {
        if (v[1].b[1] != self->unk_62.b[1]) {
            self->flags[4] = 1;
            self->flags[3] = 1;
        }
        if (v[1].b[0] != self->unk_62.b[0]) {
            self->flags[5] = 1;
        }
        self->unk_62.w = v[1].w;
    }

    if (s != self->unk_64) {
        self->flags[2] = 1;
        self->unk_64 = s;
    }
}
