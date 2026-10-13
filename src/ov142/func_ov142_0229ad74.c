/* func_ov142_0229ad74 @ 0x0229ad74, 0xec bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb4];
    s16 unk_B4;
    char pad_B6[0x184e - 0xb6];
    u16 arr[9];
} UnkStruct_0229ad74;

typedef struct {
    int b[10];
} UnkStruct_0229ad74_2;

extern void func_02062fbc(UnkStruct_0229ad74_2 *c);
extern u16 *func_ov142_0229a644(UnkStruct_0229ad74 *self, int row);
extern int func_ov142_0229a6d8(UnkStruct_0229ad74 *self);
extern void *func_ov142_0229ae8c(UnkStruct_0229ad74 *self);
extern void func_020a8c1c(void *h);
extern void func_02062ea4(UnkStruct_0229ad74_2 *c, u16 *p);
extern void func_020a8bb8(void *h, UnkStruct_0229ad74_2 *c);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);
extern void func_02062f4c(UnkStruct_0229ad74_2 *c);

void func_ov142_0229ad74(UnkStruct_0229ad74 *self)
{
    UnkStruct_0229ad74_2 ctx;
    u16 tmp;
    int i;
    void *h;
    int limit;
    int row;
    int col;
    u16 *src;

    func_02062fbc(&ctx);
    row = self->unk_B4;
    src = func_ov142_0229a644(self, row);
    col = (row + 9) % 9;
    limit = func_ov142_0229a6d8(self);
    for (i = 0; i < 9; i++) {
        h = 0;
        if (row < 0 || row >= limit) {
            self->arr[col] = 0xfff1;
            h = func_ov142_0229ae8c(self);
            func_020a8c1c(h);
        } else {
            u16 *q = (u16 *) ((char *) self + col * 2 + 0x184e);
            u16 val = *src;
            if (val != *q) {
                *q = val;
                h = func_ov142_0229ae8c(self);
                tmp = *src;
                func_02062ea4(&ctx, &tmp);
                func_020a8bb8(h, &ctx);
            }
            src++;
        }
        if (h != 0) {
            func_02070adc(h, 4, col * 0x1a + 0x52, 0xd, 0xf, 8, 0);
            func_02070a04(h, 0, 0);
        }
        row++;
        col++;
        if (col >= 9) {
            col = 0;
        }
    }
    func_02062f4c(&ctx);
}
