/* func_ov003_0222924c @ 0x0222924c, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x80 - 0x44];
    u8 unk_80;
    char pad_81[0xa4 - 0x81];
} UnkStruct_0222924c;

extern UnkStruct_0222924c data_ov003_0225f4dc[];
extern void *data_020ccf94;
extern int func_02073918(void *h, int i);
extern int func_0204fee8(u8 i);
extern void func_ov003_022291e4(char *self, int i);
extern int func_ov003_022291c8(char *self, u8 i);
extern int func_ov003_02229100(char *self, u8 i);
extern void func_0204ff00(u8 i, int a, int b, int c, int d);

void func_ov003_0222924c(char *self)
{
    void *h;
    int i;
    i = 0;
    h = data_020ccf94;
    for (; i < 4; i++) {
        int st;
        UnkStruct_0222924c *e;
        if (func_02073918(h, i)) {
            continue;
        }
        st = func_0204fee8((u8) i);
        if (st == 9) {
            st = 1;
        }
        switch (st) {
            case 0:
                func_ov003_022291e4(self, i);
                break;
            case 6:
                e = &data_ov003_0225f4dc[i];
                e->unk_80 = 1;
                func_ov003_022291e4(self, i);
                break;
            case 1:
                if (func_ov003_022291c8(self, (u8) i)) {
                    func_0204ff00((u8) i, 8, -1, 0, 0);
                } else {
                    e = &data_ov003_0225f4dc[i];
                    e->unk_40 = 4;
                }
                break;
            case 9:
                break;
            case 2:
                if (func_ov003_02229100(self, (u8) i)) {
                    func_0204ff00((u8) i, 8, -1, 0, 0);
                } else {
                    e = &data_ov003_0225f4dc[i];
                    e->unk_40 = 4;
                }
                break;
        }
    }
}
