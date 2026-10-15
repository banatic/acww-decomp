/* func_ov127_02299e64 @ 0x02299e64, 0x12c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x24];
    char unk_24;
    char pad_25[0x1024 - 0x25];
    char unk_1024;
    char pad_1025[0x2824 - 0x1025];
    s16 unk_2824;
    s16 unk_2826;
    char pad_2828[0x282e - 0x2828];
    s16 unk_282E;
    char pad_2830[2];
    u8 unk_2832;
} UnkStruct_02299e64;

extern int func_ov127_02299878(UnkStruct_02299e64 *self, int a);
extern void func_ov127_022998b4(UnkStruct_02299e64 *self);
extern void func_0200284c(int a, int b, int c);
extern void func_ov127_02299858(UnkStruct_02299e64 *self, int a);
extern void func_ov127_02299868(UnkStruct_02299e64 *self, int a);
extern void MI_CpuCopy8(void *src, void *dst, int n);
extern int func_020b9bbc(UnkStruct_02299e64 *self, void *p, int a, int b, int c);

void func_ov127_02299e64(UnkStruct_02299e64 *self)
{
    int v;
    int t;
    int n;
    u16 *p;
    int j;
    u16 *q;
    int k;
    int i;

    if (func_ov127_02299878(self, 4) != 0) {
        func_ov127_022998b4(self);
    }
    if (func_ov127_02299878(self, 1) != 0) {
        func_0200284c(self->unk_2832, self->unk_2824, self->unk_2826);
        func_ov127_02299858(self, 1);
        t = 0;
        v = self->unk_2826;
        if (v < 0) {
            t = ((v - 7) << 13) >> 16;
        } else if (v >= 0x40) {
            t = ((v - 0x39) << 13) >> 16;
        }
        if (t != self->unk_282E) {
            self->unk_282E = t;
            func_ov127_02299868(self, 2);
        }
    }
    if (func_ov127_02299878(self, 2) != 0) {
        MI_CpuCopy8(&self->unk_24, &self->unk_1024, 0x1000);
        n = self->unk_282E;
        if (n > 0) {
            p = (u16 *) &self->unk_1024;
            q = (u16 *) ((char *) p + 0x800);
            j = 0;
            for (i = 0; i < self->unk_282E; i++) {
                for (k = j; k < 0x20; k++) {
                    *p = 0x4010;
                    *q = 0x4010;
                    p++;
                    q++;
                }
            }
        } else if (n < 0) {
            p = (u16 *) ((char *) &self->unk_1024 + (n + 0x20) * 0x40);
            q = (u16 *) ((char *) p + 0x800);
            j = 0;
            for (i = 0; i > self->unk_282E; i--) {
                for (k = j; k < 0x20; k++) {
                    *p = 0x4010;
                    *q = 0x4010;
                    p++;
                    q++;
                }
            }
        }
        func_020b9bbc(self, &self->unk_1024, self->unk_2832, 0x1000, 0);
        func_ov127_02299858(self, 2);
    }
}
