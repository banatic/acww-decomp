/* func_ov114_0229cf18 @ 0x0229cf18, 0x40 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x12ae];
    unsigned char unk_12AE;
    char pad_12AF[1];
    unsigned char unk_12B0;
    char pad_12B1[4];
    unsigned char unk_12B5;
} UnkStruct_0229cf18;

extern void func_ov114_0229cf58(void);
extern void RtcSendPxiCommand(int cmd);

int func_ov114_0229cf18(UnkStruct_0229cf18 *p)
{
    if (p->unk_12B5 + 1 < p->unk_12B0) {
        p->unk_12B5 = p->unk_12B5 + 1;
        p->unk_12AE = 5;
        func_ov114_0229cf58();
        RtcSendPxiCommand(0x39);
        return 1;
    }
    return 0;
}
