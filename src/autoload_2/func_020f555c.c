/* func_020f555c @ 0x020f555c, 0x70 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 unk_00[0x61];
} GFlags;
extern GFlags data_021fd1bc;
extern void NNS_SndPlayerSetVolume(void *param1, int param2);

typedef struct {
    u8 unk_00[0x41];
} Obj2;

void func_020f555c(void *self, int idx)
{
    void *elem;
    Obj2 *adj;
    u8 raw;
    int vol;

    if (data_021fd1bc.unk_00[0x60] == 0) {
        return;
    }

    elem = (u8 *) self + 8 + idx * 0xc;
    adj = self ? (Obj2 *) ((u8 *) self - 4) : (Obj2 *) self;
    raw = adj->unk_00[0x40];
    vol = ((int) raw * 0x28) / 100;
    NNS_SndPlayerSetVolume(elem, vol);
}
