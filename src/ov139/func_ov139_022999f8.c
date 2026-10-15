/* func_ov139_022999f8 @ 0x022999f8, 0x70 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_ov139_02299e3c[];
extern const unsigned char data_ov139_02299e4c[];
extern const unsigned char data_ov139_02299e5c[];
extern void *data_021fbe94;

struct UnkStruct_022999f8 {
    char pad_00[0x960];
    unsigned char unk_960[0x20];
    unsigned char unk_980[0x20];
    char pad_9A0[2];
    unsigned char unk_9A2;
};

extern int func_02002c6c(const unsigned char *, void *, int, int, int, int);
extern int func_02002d14(const unsigned char *, void *, int, int, int, int);
extern int func_02064af4(const unsigned char *, void *, int);
extern void MIi_CpuCopy16(void *, void *, int);

void func_ov139_022999f8(struct UnkStruct_022999f8 *s)
{
    void *obj = data_021fbe94;
    func_02002c6c(data_ov139_02299e3c, obj, s->unk_9A2, 0x11, 0x11, 0x36);
    func_02002d14(data_ov139_02299e4c, obj, s->unk_9A2, 1, 1, 8);
    func_02064af4(data_ov139_02299e5c, s->unk_960, 0x20);
    MIi_CpuCopy16(s->unk_960, s->unk_980, 0x20);
}
