/* func_ov091_02299004 @ 0x02299004, 0x4c bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_before[0x8c];
    unsigned char unk_8C;
    char pad_after[0x3bc - 0x8d];
} UnkStruct_02299004;

extern int func_ov002_02208054(UnkStruct_02299004 *self, int a);
extern void func_ov091_02298f9c(UnkStruct_02299004 *self);
extern int MATH_CalcMD5(char *ptr);
extern void func_0208f0c4(char *ptr, int a);
extern void func_ov002_022080a0(UnkStruct_02299004 *self, int a);
extern void RtcSendPxiCommand(int cmd);

void func_ov091_02299004(UnkStruct_02299004 *self)
{
    if (func_ov002_02208054(self, 1)) {
        func_ov091_02298f9c(self);
        return;
    }
    if (MATH_CalcMD5((char *) self + 0x3bc)) {
        func_0208f0c4((char *) self + 0x3bc, 2);
        self->unk_8C = 3;
        func_ov002_022080a0(self, 1);
        RtcSendPxiCommand(0x27);
    }
}
