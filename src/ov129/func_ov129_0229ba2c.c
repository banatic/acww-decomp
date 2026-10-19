/* func_ov129_0229ba2c @ 0x0229ba2c, 0x1ac bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xaa];
    u16 unk_AA;
    char pad_AC[0xb1 - 0xac];
    u8 b1;
    char pad_B2[1];
    u8 b3;
    char pad_B4[0x1d4 - 0xb4];
    char unk_1D4[0x2f78 - 0x1d4];
    u16 arr[0x10];     // 0x2f78
    u8 unk_2F98[0x10]; // 0x2f98
} UnkStruct_0229ba2c;

extern int func_ov129_0229bcf0(UnkStruct_0229ba2c *, u16);
extern void func_ov002_0220a658(void *, int);
extern void func_0200467c(int);
extern u8 *func_ov127_022996bc(u16);
extern int func_ov127_022996d8(u8);
extern int func_ov127_022996c8(u8);
extern int func_ov127_022996e4(u16 *, int, int);
extern int func_ov129_0229bca4(UnkStruct_0229ba2c *, u8);

int func_ov129_0229ba2c(UnkStruct_0229ba2c *self)
{
    u8 *p;
    char *mp;
    u16 *slot;
    int n;
    int i;
    int k;
    int cnt;
    int changed;
    int m;
    int r;
    int t;
    int u;
    int idx;
    u8 *q;
    u8 c;
    u8 marks[16];
    u16 buf[8];

    k = func_ov129_0229bcf0(self, self->unk_AA);
    if (k == -1) {
        return 0;
    }
    slot = &self->arr[k];
    *slot = 0xffff;

    changed = 1;
    cnt = 0;
    for (i = 0; i < 16; i++) {
        if (self->arr[i] == 0xffff) {
            marks[i] = 3;
        } else {
            if (cnt > 0) {
                marks[i] = 0;
            } else {
                marks[i] = 1;
            }
            cnt++;
        }
    }
    if (cnt == 0) {
        func_ov002_0220a658(self->unk_1D4, 6);
        self->b1 = 0;
        self->b3 = 0xff;
        func_0200467c(0x882);
        return 2;
    }
    while (changed) {
        changed = 0;
        for (i = 0; i < 16; i++) {
            mp = (char *) &marks[i];
            if (marks[i] == 1) {
                p = func_ov127_022996bc(self->arr[i]);
                for (m = 0; m < 2; m++) {
                    t = func_ov127_022996d8(p[m]);
                    u = func_ov127_022996c8(p[m]);
                    n = func_ov127_022996e4(buf, t, u);
                    for (r = 0; r < n; r++) {
                        idx = func_ov129_0229bcf0(self, buf[r]);
                        if (idx != -1) {
                            q = &marks[idx];
                            if (marks[idx] == 0) {
                                *q = 1;
                            }
                        }
                    }
                }
                *mp = 2;
            }
        }
        for (i = 0; i < 16; i++) {
            if (marks[i] == 1) {
                changed = 1;
            }
        }
    }
    for (i = 0; i < 16; i++) {
        if (marks[i] == 0) {
            *slot = self->unk_AA;
            return 0;
        }
    }

    p = func_ov127_022996bc(self->unk_AA);
    c = 0xff;
    if (p[0] == self->b3) {
        c = p[1];
    } else if (p[1] == self->b3) {
        c = p[0];
    }
    if (c != 0xff) {
        self->unk_2F98[self->unk_AA] = 0;
        if (func_ov129_0229bca4(self, self->b3) == 0) {
            self->b3 = c;
        }
    }
    func_0200467c(0x882);
    return 2;
}
