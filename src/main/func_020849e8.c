/* func_020849e8 @ 0x020849e8, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[8];
    int unk_08;
} UnkStruct_020849e8;

extern u8 data_020e54a8;
extern void *data_021c80bc;
extern int func_0204f490(void *, int *, int *, int *, int *, u16 *, u16 *, int, int);
extern void func_0204f7ac(int a, int b, int c, int d, int e);

int func_020849e8(void *unused, UnkStruct_020849e8 *self)
{
    unsigned int ok;
    void *g;
    u16 pair[2];
    int v4, v5, v6, v7;

    ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok != 0) {
        g = data_021c80bc;
        v4 = 0;
        v5 = 0;
        v6 = 0;
        v7 = 0;
        if (g != 0) {
            pair[0] = 0x5014;
            pair[1] = 0x501a;
            if (func_0204f490(g, &v4, &v5, &v6, &v7, &pair[0], &pair[1], 1, 0) != 0) {
                func_0204f7ac((int) self, v4, v5, v6, v7);
                self->unk_08 += 0x4000;
                return 1;
            }
        }
    }
    return 0;
}
