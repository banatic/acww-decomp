/* func_ov068_022730c8 @ 0x022730c8, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *, int);
extern void RtcSendPxiCommand(int);
extern void func_ov068_02273230(void *, int);

typedef struct {
    char pad_00[0x598];
    unsigned short unk_598;
    short unk_59A;
} UnkStruct_022730c8;

void func_ov068_022730c8(UnkStruct_022730c8 *self)
{
    if (func_02056f28((char *) self + 0x188, 0) != 0) {
        RtcSendPxiCommand(0x886);
    } else if (func_02056f28((char *) self + 0x188, 0x1c) != 0) {
        RtcSendPxiCommand(0x887);
    }
    if (self->unk_598 % 3 == 0) {
        if (self->unk_59A >= 0) {
            self->unk_59A--;
            if (self->unk_59A == 0) {
                func_ov068_02273230(self, 2);
            }
        }
    }
    self->unk_598++;
}
