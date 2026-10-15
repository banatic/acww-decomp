/* func_0206aa80 @ 0x0206aa80, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int cmd);
extern void func_02067f28(int a, int b, int c, int d, int e);

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_0206aa80;

void func_0206aa80(UnkStruct_0206aa80 *param)
{
    RtcSendPxiCommand(7);
    func_02067f28(param->unk_24, 0xa000, 0x800, 0x800, 0x1333);
}
