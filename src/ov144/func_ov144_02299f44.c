/* func_ov144_02299f44 @ 0x02299f44, 0xfc bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb6];
    s16 unk_B6;
    s16 unk_B8;
    char pad_BA[0x86c - 0xba];
    u16 src[9];
    char pad_87E[0x8f8 - 0x87e];
    u16 arr[9];
} UnkStruct_02299f44;

typedef struct {
    int b[10];
} UnkStruct_02299f44_2;

extern void *func_02062fbc(UnkStruct_02299f44_2 *c);
extern void *func_ov144_0229a06c(UnkStruct_02299f44 *self);
extern void func_020a8c1c(void *h);
extern int func_02062ea4(UnkStruct_02299f44_2 *c, u16 *p);
extern void *func_020a8bb8(void *h, UnkStruct_02299f44_2 *c);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);
extern void *func_02062f4c(UnkStruct_02299f44_2 *c);

void func_ov144_02299f44(UnkStruct_02299f44 *self)
{
    UnkStruct_02299f44_2 ctx;
    u16 tmp;
    int i;
    void *h;
    int limit;
    int row;
    int col;
    u16 *src;

    func_02062fbc(&ctx);
    row = self->unk_B6;
    if (row < 0) {
        src = self->src;
    } else {
        src = &self->src[row];
    }
    col = (row + 9) % 9;
    limit = self->unk_B8;
    for (i = 0; i < 9; i++) {
        h = 0;
        if (row < 0 || row >= limit) {
            self->arr[col] = 0xfff1;
            h = func_ov144_0229a06c(self);
            func_020a8c1c(h);
        } else {
            if (*src != self->arr[col]) {
                self->arr[col] = *src;
                h = func_ov144_0229a06c(self);
                tmp = *src;
                func_02062ea4(&ctx, &tmp);
                func_020a8bb8(h, &ctx);
            }
            src++;
        }
        if (h != 0) {
            func_02070adc(h, 4, col * 0x1a + 0x184, 0xd, 0xf, 7, 0);
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
