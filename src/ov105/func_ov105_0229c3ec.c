/* func_ov105_0229c3ec @ 0x0229c3ec, 0x4c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(unsigned int command);
extern void func_ov002_02207d24(void *ptr, unsigned int value);
extern void func_ov105_0229cfc0(void *self);
extern void func_ov002_022080a0(void *self, unsigned int value);
extern void func_ov105_0229c330(void *self, unsigned int value);
extern unsigned short data_ov105_0229f85c[];

struct UnkStruct_0229c3ec {
    char pad_00[0x8c];
    unsigned char unk_8C;
    char pad_8D[0x2c0 - 0x8d];
    unsigned char unk_2C0;
    char pad_2C1[0x23bc - 0x2c1];
    unsigned char unk_23BC[1];
};

void func_ov105_0229c3ec(struct UnkStruct_0229c3ec *self)
{
    RtcSendPxiCommand(data_ov105_0229f85c[self->unk_2C0]);
    func_ov002_02207d24(&self->unk_23BC, 1);
    func_ov105_0229cfc0(self);
    self->unk_8C = 0xb;
    func_ov002_022080a0(self, 1);
    func_ov105_0229c330(self, 0x40);
}
