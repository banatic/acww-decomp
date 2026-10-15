/* func_ov122_022a07d4 @ 0x022a07d4, 0x74 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

typedef struct {
    unsigned char pad_00[0xAC];
    unsigned char unk_AC;
    unsigned char unk_AD;
    unsigned char unk_AE;
} UnkStruct_022a07d4;

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov122_0229efc8(UnkStruct_022a07d4 *p, int a);
extern int func_ov002_02208008(void *unused0);
extern int func_ov122_0229f684(UnkStruct_022a07d4 *p, int a, int b);
extern void func_ov122_022a15b8(UnkStruct_022a07d4 *p, int a, int b);
extern void func_ov122_0229f9a8(UnkStruct_022a07d4 *p);
extern void func_ov122_0229f1b4(UnkStruct_022a07d4 *p);
extern void RtcSendPxiCommand(int cmd);

void func_ov122_022a07d4(UnkStruct_022a07d4 *param)
{
    if ((data_021fbe40 & 1) == 0) {
        func_ov002_02208098((void *) (param), 0xc);
        if (param->unk_AD == param->unk_AE) {
            func_ov122_0229efc8(param, 8);
        }
    } else {
        int ret = func_ov002_02208008(param);
        if (func_ov122_0229f684(param, ret, 0) != 0) {
            param->unk_AE = param->unk_AC;
            func_ov122_022a15b8(param, 0, 1);
            func_ov122_0229f9a8(param);
            func_ov122_0229f1b4(param);
            RtcSendPxiCommand(0x15);
        }
    }
}
