/* func_020aa3f4 @ 0x020aa3f4, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int id, int index);
extern void RtcSendPxiCommand(int cmd);

struct UnkStruct_020aa3f4 {
    char pad_00[8];
    int unk_08;
    char pad_0C[176];
    int unk_BC;
    char unk_C0;
};

void func_020aa3f4(struct UnkStruct_020aa3f4 *p)
{
    p->unk_08 = 3;
    p->unk_C0 = 1;
    p->unk_BC = func_0209d368(0x65, 2) + 2;
    RtcSendPxiCommand(0x14);
}
