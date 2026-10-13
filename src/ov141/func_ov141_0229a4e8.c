/* func_ov141_0229a4e8 @ 0x0229a4e8, 0x3c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a4e8 {
    unsigned char pad_00[0x1278];
    int unk_1278;
    unsigned char pad_127C[0x80f];
    unsigned char unk_1A8B;
};

extern void func_ov141_02299f6c(struct UnkStruct_0229a4e8 *p, int n);
extern void func_ov002_02208090(struct UnkStruct_0229a4e8 *p, int n);
extern void func_ov002_02208098(struct UnkStruct_0229a4e8 *p, int n);
extern void RtcSendPxiCommand(int cmd);

void func_ov141_0229a4e8(struct UnkStruct_0229a4e8 *param)
{
    func_ov141_02299f6c(param, 2);
    param->unk_1278 = 10;
    param->unk_1A8B = 5;
    func_ov002_02208090(param, 3);
    func_ov002_02208098(param, 5);
    RtcSendPxiCommand(0x28);
}
