/* func_020a9e8c @ 0x020a9e8c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int id, int index);
extern void RtcSendPxiCommand(int command);

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x188];
    int unk_194;
    char unk_198;
} UnkStruct_020a9e8c;

void func_020a9e8c(UnkStruct_020a9e8c *object)
{
    object->unk_08 = 3;
    object->unk_198 = 1;
    object->unk_194 = func_0209d368(0x65, 2) + 2;
    RtcSendPxiCommand(0x14);
}
