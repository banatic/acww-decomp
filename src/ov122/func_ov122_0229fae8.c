/* func_ov122_0229fae8 @ 0x0229fae8, 0x6a bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229efe8(void *p, int val);
extern void func_ov122_0229fea4(void *self);
extern void func_ov122_0229fd88(void *self, int arg);
extern void func_ov122_0229fcfc(void *self);
extern void func_ov122_0229f394(void *self);

struct UnkStruct_0229fae8 {
    char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
};

void func_ov122_0229fae8(struct UnkStruct_0229fae8 *self, int b, int c, int d)
{
    if (!func_ov122_0229efe8(self, 0x10) && c < 0x3c) {
        self->unk_9C = b;
        func_ov122_0229fea4(self);
    } else if (c < 0x84) {
        if (c < 0x40) {
            c = 0x40;
        } else if (c >= 0x80) {
            c = 0x7f;
        }
        self->unk_9C = b;
        self->unk_A0 = c;
        func_ov122_0229fd88(self, d);
    } else {
        self->unk_9C = b;
        func_ov122_0229fcfc(self);
    }
    func_ov122_0229f394(self);
}
