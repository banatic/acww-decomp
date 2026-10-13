/* func_ov123_0229b8ec @ 0x0229b8ec, 0xd0 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char a8;
    unsigned char a9;
    unsigned char pad_AA[2];
    unsigned char ac;
    unsigned char pad_AD[2];
    unsigned char af;
    unsigned char b0;
} UnkStruct_0229b8ec;

extern int func_ov002_02208014(UnkStruct_0229b8ec *self);
extern int func_ov002_02208008(UnkStruct_0229b8ec *self);
extern int func_ov123_022999b0(UnkStruct_0229b8ec *self, int r1, int r2);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov123_02299ec4(UnkStruct_0229b8ec *self);
extern void func_ov123_0229b6d0(UnkStruct_0229b8ec *self);
extern void func_ov123_02299ea8(UnkStruct_0229b8ec *self);
extern void func_ov123_0229b65c(UnkStruct_0229b8ec *self);
extern void func_ov123_02299980(UnkStruct_0229b8ec *self);
extern unsigned short data_021fbe40[2];

void func_ov123_0229b8ec(UnkStruct_0229b8ec *self)
{
    if (func_ov002_02208014(self) != 0) {
        RtcSendPxiCommand(0x86e);
        func_ov123_02299ec4(self);
        func_ov123_0229b6d0(self);
        return;
    }
    {
        int r = func_ov002_02208008(self);
        if (func_ov123_022999b0(self, r, 0) != 0) {
            self->a8 = self->af;
            self->a9 = self->b0;
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40[1];
        if (flags & 1) {
            func_ov123_02299ea8(self);
            return;
        }
        if (flags & 2) {
            RtcSendPxiCommand(0x86e);
            func_ov123_02299ec4(self);
            func_ov123_0229b65c(self);
            return;
        }
        if (flags & 0x800) {
            RtcSendPxiCommand(0x864);
            func_ov123_02299ec4(self);
            self->ac = 0;
            func_ov123_0229b65c(self);
            return;
        }
        if (flags & 0x400) {
            func_ov123_02299980(self);
        }
    }
}
