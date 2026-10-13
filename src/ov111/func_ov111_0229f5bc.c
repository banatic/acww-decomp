/* func_ov111_0229f5bc @ 0x0229f5bc, 0x44 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern void func_ov111_0229f598(void *self, int val);
extern void RtcSendPxiCommand(int cmd);

struct UnkStruct_0229f5bc {
    char pad_00[0x9e];
    unsigned char unk_9E;
    unsigned char pad_9F;
    unsigned char unk_A0;
};

void func_ov111_0229f5bc(struct UnkStruct_0229f5bc *self)
{
    int val;
    val = data_021f6c58;
    if (val < 0x18) {
        val = 0x18;
    }
    if (val >= 0xc8) {
        val = 0xc7;
    }
    func_ov111_0229f598(self, val);
    if (self->unk_A0 != self->unk_9E) {
        RtcSendPxiCommand(0x15);
    }
    self->unk_A0 = self->unk_9E;
}
