/* func_ov003_02232aa0 @ 0x02232aa0, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232aa0;
extern UnkStruct_02232aa0 *data_020ccf94;

extern int func_02073dd4(void *a, int b);
extern int func_ov003_02219d04(int *p, int i);
extern char *func_ov003_022356ec(int *p);
extern int func_0200322c(int *p, char *q);
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *m, int a, int b);

int func_ov003_02232aa0(char *self, short *out)
{
    s8 *st;
    int *p;
    s8 i;
    char *q;
    int ang;

    st = (s8 *) (self + 0x24e);
    p = (int *) (self + 0x204);
    if (*st <= 0) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
            for (i = 0; i < 4; i++) {
                *st = (s8) func_ov003_02219d04(p, i);
                if (*st > 0) {
                    break;
                }
            }
        } else {
            *st = (s8) func_ov003_02219d04(p, 4);
        }
    }
    if (*st > 0) {
        *st = *st - 1;
        if (*st == 0) {
            q = func_ov003_022356ec(p);
            if (q != 0) {
                ang = func_0200322c(p, q + 0x5c);
                *(u8 *) (self + 0x251) = 5;
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0x1f);
                *(short *) (self + 0x23a) = ang + 0x8000;
                *out = 0;
                return 1;
            }
        }
    }
    return 0;
}
