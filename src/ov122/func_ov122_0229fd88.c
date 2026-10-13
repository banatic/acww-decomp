/* func_ov122_0229fd88 @ 0x0229fd88, 0xa0 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xaa - 0xa4];
    unsigned char unk_AA;
    char pad_AB[0xb2 - 0xab];
    unsigned char unk_B2;
    char pad_B3[0x3ce8 - 0xb3];
    char unk_3CE8;
} UnkStruct_0229fd88;

extern void func_ov122_0229efd8(UnkStruct_0229fd88 *, int);
extern int func_0206de70(void *);
extern void func_ov122_0229fcfc(UnkStruct_0229fd88 *);
extern int func_ov122_0229fd34(UnkStruct_0229fd88 *, int, void *);
extern void func_ov122_0229f590(UnkStruct_0229fd88 *, int);

void func_ov122_0229fd88(UnkStruct_0229fd88 *self, int flag)
{
    int n, result, ret;

    self->unk_AA = 2;
    func_ov122_0229efd8(self, 0x1000);

    if (self->unk_A0 < 0x40) {
        self->unk_A0 = 0x40;
    }
    if (self->unk_A0 >= 0x80) {
        self->unk_A0 = 0x7f;
    }

    n = (self->unk_A0 - 0x40) >> 4;
    result = func_0206de70((void *) &self->unk_3CE8);

    if (n > result) {
        n = result;
    } else {
        flag = 0;
    }

    self->unk_A0 = (n << 4) + 0x40;

    if (flag != 0) {
        if ((self->unk_A0 - self->unk_B2) < 8) {
            func_ov122_0229fcfc(self);
            return;
        }
    }

    ret = func_ov122_0229fd34(self, n, (void *) ((char *) self + 0x9c));
    func_ov122_0229f590(self, ret);
}
