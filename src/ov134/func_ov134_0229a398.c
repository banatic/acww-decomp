/* func_ov134_0229a398 @ 0x0229a398, 0x4a bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char pad_A5[4];
    unsigned char unk_A9;
    unsigned char pad_AA[5];
    unsigned char unk_AF;
} UnkStruct_0229a398;

extern void RtcSendPxiCommand(int cmd);
extern void func_02001b6c(int a);
extern void func_02001d74(int a, int b);
extern int func_02002d8c(int x);
extern void func_02001d00(int x);
extern void func_ov134_022995a0(UnkStruct_0229a398 *p, int a);

void func_ov134_0229a398(UnkStruct_0229a398 *p)
{
    RtcSendPxiCommand(0x2a);
    p->unk_A9 = 4;
    p->unk_AF = 3;
    func_02001b6c(1);
    func_02001d74(0x1f, 1);
    func_02001d00(~func_02002d8c(p->unk_A4) & 0x1f);
    func_ov134_022995a0(p, 4);
}
