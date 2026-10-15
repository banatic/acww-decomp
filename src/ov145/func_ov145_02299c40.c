/* func_ov145_02299c40 @ 0x02299c40, 0x164 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb6];
    s16 unk_B6;
    char pad_B8[0xcb4 - 0xb8];
    u16 arr[9];
} UnkStruct_02299c40;

typedef struct {
    int b[10];
} UnkStruct_02299c40_2;
typedef struct {
    int b[8];
} Ctx2;

extern char data_021f38f8[];

extern void *func_02094fd4(Ctx2 *c);
extern void *func_02094fbc(Ctx2 *c);
extern void *func_02062fbc(UnkStruct_02299c40_2 *c);
extern void *func_02062f4c(UnkStruct_02299c40_2 *c);
extern u16 *func_ov145_022999c4(UnkStruct_02299c40 *self, int row);
extern int func_ov145_02299a24(UnkStruct_02299c40 *self);
extern void *func_ov145_02299dd0(UnkStruct_02299c40 *self);
extern void func_020a8c1c(void *h);
extern int func_02062ea4(UnkStruct_02299c40_2 *c, u16 *p);
extern void *func_020a8bb8(void *h, void *c);
extern int func_02070fe4(char *t, Ctx2 *c, u16 *p);
extern int func_0207094c(void *h, int a);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);

void func_ov145_02299c40(UnkStruct_02299c40 *self)
{
    Ctx2 ctx2;
    UnkStruct_02299c40_2 ctx;
    u16 tmp[2];
    int i;
    void *h;
    void *h2;
    int limit;
    int row;
    int col;
    u16 *src;

    func_02094fd4(&ctx2);
    func_02062fbc(&ctx);
    row = self->unk_B6;
    src = func_ov145_022999c4(self, row);
    col = (row + 9) % 9;
    limit = func_ov145_02299a24(self);
    for (i = 0; i < 9; i++) {
        h = 0;
        if (row < 0 || row >= limit) {
            self->arr[col] = 0xfff1;
            h = func_ov145_02299dd0(self);
            func_020a8c1c(h);
            h2 = func_ov145_02299dd0(self);
            func_020a8c1c(h2);
        } else {
            if (*src != self->arr[col]) {
                self->arr[col] = *src;
                h = func_ov145_02299dd0(self);
                tmp[0] = *src;
                func_02062ea4(&ctx, &tmp[0]);
                func_020a8bb8(h, &ctx);
                h2 = func_ov145_02299dd0(self);
                tmp[1] = *src;
                if (func_02070fe4(data_021f38f8, &ctx2, &tmp[1]) != 0) {
                    func_020a8bb8(h2, &ctx2);
                } else {
                    func_0207094c(h2, 0xcc);
                }
            }
            src++;
        }
        if (h != 0) {
            func_02070adc(h, 4, col * 0x1a + 0x184, 0xd, 0xf, 7, 0);
            func_02070a04(h, 0, 0);
            func_02070adc(h2, 4, col * 0x10 + 0xf4, 8, 0xf, 7, 0);
            func_02070a04(h2, 0, 0);
        }
        row++;
        col++;
        if (col >= 9) {
            col = 0;
        }
    }
    func_02062f4c(&ctx);
    func_02094fbc(&ctx2);
}
