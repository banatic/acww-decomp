/* func_0206aab0 @ 0x0206aab0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_02067f28(int, int, int, int, int);

struct UnkStruct_0206aab0 {
    char pad_00[0x24];
    unsigned int unk_24;
};

void func_0206aab0(struct UnkStruct_0206aab0 *param)
{
    RtcSendPxiCommand(6);
    func_02067f28(param->unk_24, 0x6000, 0x666, 0x4cc, 0x1199);
}
