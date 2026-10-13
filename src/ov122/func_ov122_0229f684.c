/* func_ov122_0229f684 @ 0x0229f684, 0x218 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x44];
    char unk_44;
    char pad1[0x58 - 0x45];
    char unk_58;
    char pad2[0xd8 - 0x59];
    char unk_D8;
    char pad3[0xf8 - 0xd9];
    unsigned char unk_F8;
} UnkStruct_0229f684;

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    char pad1[0xaa - 0xa4];
    unsigned char unk_AA;
    char pad2[1];
    unsigned char unk_AC;
    char pad3[0xbc - 0xad];
    UnkStruct_0229f684 *unk_BC;
    char pad_C0[0x3ce8 - 0xc0];
    char unk_3CE8;
} UnkStruct_0229f684_2;

extern int func_0206de70(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov122_0229efe8(UnkStruct_0229f684_2 *, int);
extern unsigned char func_ov122_0229fe28(UnkStruct_0229f684_2 *, int, void *);
extern unsigned char func_ov122_0229fc9c(UnkStruct_0229f684_2 *, void *);
extern unsigned char func_ov122_0229fd34(UnkStruct_0229f684_2 *, int, void *);
extern int func_02051c8c_unk(void *, int);
extern void func_ov122_0229efd8(UnkStruct_0229f684_2 *, int);
extern void func_ov122_0229f590(UnkStruct_0229f684_2 *, int);

int func_ov122_0229f684(UnkStruct_0229f684_2 *self, void *pad, int force)
{
    unsigned char mode;
    int val;
    int n;
    int start;
    int limit;
    int max;
    unsigned char cur;

    if (pad == 0) {
        return 0;
    }

    mode = self->unk_AA;
    cur = self->unk_AC;
    limit = func_0206de70(&self->unk_3CE8);

    switch (mode) {
        case 0:
        case 1:
            n = -1;
            start = n;
            if (func_ov002_022088bc(pad)) {
                n = 0;
            }
            break;
        case 2:
            n = (self->unk_A0 - 0x40) >> 4;
            start = n;
            if (func_ov002_022088cc(pad)) {
                n--;
            } else if (func_ov002_022088bc(pad)) {
                n++;
                if (n > limit) {
                    n = 4;
                }
            }
            break;
        case 3:
            n = 4;
            start = n;
            if (func_ov002_022088cc(pad)) {
                n--;
            }
            break;
        default:
            n = 0;
            start = n;
            break;
    }

    val = self->unk_9C;
    if (func_ov122_0229efe8(self, 0x10) && n == -1) {
        n = 0;
    }

    if (n != start) {
        if (n == -1) {
            cur = func_ov122_0229fe28(self, val, &mode);
        } else if (n >= 4) {
            mode = 3;
            cur = func_ov122_0229fc9c(self, &val);
        } else {
            mode = 2;
            cur = func_ov122_0229fd34(self, n, &val);
        }
    }

    if (func_ov002_022088ac(pad)) {
        if (cur != 0) {
            cur = cur - 1;
        } else if (mode == 1) {
            cur = self->unk_BC->unk_F8;
            mode = 0;
        }
    } else if (func_ov002_0220889c(pad)) {
        switch (mode) {
            case 0:
                max = self->unk_BC->unk_F8;
                break;
            case 1:
                max = func_02051c8c_unk(&self->unk_BC->unk_44, 0xa) - self->unk_BC->unk_F8;
                break;
            case 2:
                max = func_02051c8c_unk(&self->unk_BC->unk_58, 0x40);
                break;
            case 3:
                max = func_02051c8c_unk(&self->unk_BC->unk_D8, 0x10);
                break;
        }
        if (cur + 1 <= max) {
            cur = cur + 1;
        } else if (mode == 0) {
            cur = 0;
            mode = 1;
        }
    }

    if (mode != self->unk_AA && force == 0) {
        return 0;
    }
    if (mode == self->unk_AA && cur == self->unk_AC) {
        return 0;
    }

    self->unk_AA = mode;
    func_ov122_0229efd8(self, 0x1000);
    func_ov122_0229f590(self, cur);
    return 1;
}
