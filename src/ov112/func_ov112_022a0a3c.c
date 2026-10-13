/* func_ov112_022a0a3c @ 0x022a0a3c, 0x74 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

extern void func_ov002_02208098(void *obj, int arg);
extern int func_ov002_02208008(void *obj);
extern int func_ov112_0229f56c(void *obj, int arg);
extern void func_ov112_0229fd20(void *obj);
extern void func_ov112_0229f668(void *obj);
extern void func_ov112_0229f2bc(void *obj);
extern void func_ov112_0229fe50(void *obj, int arg);
extern void RtcSendPxiCommand(int cmd);

typedef struct {
    unsigned char pad_00[0xbd];
    unsigned char unk_BD;
    unsigned char unk_BE;
    unsigned char unk_BF;
} UnkStruct_022a0a3c;

void func_ov112_022a0a3c(UnkStruct_022a0a3c *obj)
{
    if (!(data_021fbe40 & 1)) {
        func_ov002_02208098(obj, 0xc);
        if (obj->unk_BE != obj->unk_BF) {
            return;
        }
        func_ov112_0229fe50(obj, 0x100);
    } else {
        int ret = func_ov002_02208008(obj);
        if (func_ov112_0229f56c(obj, ret) != 0) {
            obj->unk_BF = obj->unk_BD;
            func_ov112_0229fd20(obj);
            func_ov112_0229f668(obj);
            func_ov112_0229f2bc(obj);
            RtcSendPxiCommand(0x15);
        }
    }
}
