/* func_ov130_02299d48 @ 0x02299d48, 0x50 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x4];
    unsigned char unk_04;
    unsigned char pad_05[0x7];
    int unk_0C;
    int unk_10;
} UnkStruct_02299d48;

extern int func_ov130_02299d98(UnkStruct_02299d48 *self);
extern void func_ov130_02299dc8(int value);
extern void func_ov130_02299c08(UnkStruct_02299d48 *self);
extern int RtcSendPxiCommand(int command);

void func_ov130_02299d48(UnkStruct_02299d48 *self)
{
    int base;
    int val;
    int max;
    unsigned char idx;

    base = self->unk_0C;
    idx = self->unk_04;

    if (idx == 10) {
        if (func_ov130_02299d98(self) != 0) {
            return;
        }
        RtcSendPxiCommand(0x34);
        return;
    } else {
        val = idx + 10 * base;
        max = self->unk_10;
        if (val > max) {
            val = max;
        }
        if (val == base) {
            RtcSendPxiCommand(0x34);
        } else {
            func_ov130_02299dc8(idx);
            self->unk_0C = val;
            func_ov130_02299c08(self);
        }
    }
}
