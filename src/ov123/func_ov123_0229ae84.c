/* func_ov123_0229ae84 @ 0x0229ae84, 0x124 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa1];
    unsigned char unk_A1;
    char pad_A2[3];
    unsigned char unk_A5;
    char pad_A6[4];
    unsigned char unk_AA;
} UnkStruct_0229ae84;

extern void func_ov123_0229b5cc(UnkStruct_0229ae84 *);
extern void func_ov123_0229b598(UnkStruct_0229ae84 *);
extern void func_ov123_0229a278(UnkStruct_0229ae84 *, unsigned char arg1);
extern void func_ov123_0229a248(UnkStruct_0229ae84 *, unsigned char arg1);
extern void func_ov123_0229b0dc(UnkStruct_0229ae84 *, unsigned char);
extern void RtcSendPxiCommand(int);
extern void func_ov123_02299dc4(UnkStruct_0229ae84 *);
extern void func_ov123_0229b160(UnkStruct_0229ae84 *, unsigned char);
extern void func_ov123_02299980(UnkStruct_0229ae84 *);
extern void func_ov123_0229b56c(UnkStruct_0229ae84 *, int, int);
extern int func_ov123_02299650(UnkStruct_0229ae84 *, int);
extern void func_0206fc4c(int);
extern int func_0206fca4(void);
extern void func_ov123_0229b41c(UnkStruct_0229ae84 *);
extern void func_ov123_0229b384(UnkStruct_0229ae84 *);

void func_ov123_0229ae84(UnkStruct_0229ae84 *self)
{
    unsigned char cmd;

    cmd = self->unk_A5;

    if (cmd == 0x1d) {
        func_ov123_0229b5cc(self);
        return;
    }

    if (cmd == 0x1e) {
        func_ov123_0229b598(self);
        return;
    }

    if (cmd <= 0xb && cmd != 5) {
        func_ov123_0229a278(self, cmd);
        return;
    }

    if (cmd == 0xc) {
        unsigned char val;

        func_ov123_0229a248(self, cmd);
        val = (unsigned char) ((self->unk_A1 + 1) & 0xf);
        func_ov123_0229b0dc(self, val);
        RtcSendPxiCommand(0x868);
        return;
    }

    if (cmd == 5) {
        func_ov123_0229a248(self, cmd);
        func_ov123_02299dc4(self);
        return;
    }

    if (cmd >= 0xe && cmd <= 0x1c) {
        unsigned char idx;

        idx = (unsigned char) (cmd - 0xd);
        func_ov123_0229b160(self, idx);
        RtcSendPxiCommand(0x86a);
        return;
    }

    if (cmd == 0xd) {
        func_ov123_02299980(self);
    }

    if (self->unk_A5 == 0x1f) {
        int state;

        func_ov123_0229b56c(self, 2, 3);
        if (func_ov123_02299650(self, 8) != 0) {
            func_0206fc4c(0);
            RtcSendPxiCommand(0x28);
        } else {
            state = func_0206fca4();
            if (state == 2) {
                goto LA;
            }
            if (state != 3) {
                goto LC;
            }
            goto LB;
        LA:
            func_ov123_0229b41c(self);
            goto LC;
        LB:
            func_ov123_0229b384(self);
        LC:
            func_0206fc4c(1);
            RtcSendPxiCommand(0x27);
        }
        return;
    }

    if (self->unk_A5 == 0x20) {
        func_ov123_0229b56c(self, 9, 4);
        if (func_ov123_02299650(self, 8) != 0) {
            self->unk_AA = 0x1e;
            RtcSendPxiCommand(0x29);
        } else {
            self->unk_AA = 0x1d;
            RtcSendPxiCommand(0x2a);
        }
        return;
    }
}
