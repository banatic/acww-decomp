/* func_ov003_0222f320 @ 0x0222f320, 0x138 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222f320;
extern UnkStruct_0222f320 *data_020ccf94;

extern volatile u8 data_ov003_02260534;
extern u8 data_ov003_02260538;
extern char data_ov003_02260bf0[];

extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern void func_ov003_0222d300(void);
extern int func_ov003_0222da9c(void *self, int a, int b, int c);
extern int func_ov003_0222d484(s8 *a, s8 *b, int c);
extern int func_ov003_0222db40(void *self, int a, u8 b, int c);
extern void func_ov068_0226fe00(char *p);
extern int func_02096614(int *a, int *b, int *c, int d, int e);
extern void func_ov003_0222dec4(void *self, int a, int b, int c, int d);
extern void func_ov003_0222ddb8(void *self, int a);

void func_ov003_0222f320(void *self)
{
    s8 b[4];
    int x;
    int y;
    int z;
    int on;
    u8 v;
    u8 i;

    on = func_02073dd4(data_020ccf94, data_020ccf94->unk_64);
    if (on == 0 || func_020a7278() != 0) {
        if (data_ov003_02260534 % 0x14 == 0) {
            func_ov003_0222d300();
        }
        data_ov003_02260534 = data_ov003_02260534 + 1;
        v = data_ov003_02260534;
        if (v == 0x3c) {
            func_ov003_0222da9c(self, 1, 0, -1);
            data_ov003_02260534 = 0;
        } else if (v == 0x28 && on == 0) {
            b[0] = 0;
            b[1] = -1;
            if (func_ov003_0222d484(&b[0], &b[1], 1) != 0 && func_ov003_0222da9c(self, 1, b[0], b[1]) != 0) {
                data_ov003_02260534 = 0;
            }
        } else if (v == 0x14 && on == 0) {
            b[2] = 0;
            b[3] = -1;
            if (func_ov003_0222d484(&b[2], &b[3], 0) != 0 && func_ov003_0222db40(self, b[2], (u8) b[3], 2) != 0) {
                func_ov068_0226fe00(data_ov003_02260bf0);
                data_ov003_02260538 = 0;
            }
        }
    }
    if (on != 0) {
        for (i = 0; i < 4; i++) {
            if (func_02096614(&x, &y, &z, -1, i) != 0 && *(u8 *) &x == 0) {
                func_ov003_0222dec4(self, 1, i, y, z);
            }
        }
    } else {
        func_ov003_0222ddb8(self, 1);
        func_ov003_0222ddb8(self, 2);
    }
}
