/* func_ov123_0229b9bc @ 0x0229b9bc, 0xe8 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b9bc {
    unsigned char pad_00[0xa2];
    unsigned char a2;
    unsigned char pad_A3[0xa4 - 0xa3];
    unsigned char a4;
    unsigned char pad_A5[0xaf - 0xa5];
    unsigned char af;
    unsigned char b0;
    unsigned char pad_B1[0xb3 - 0xb1];
    unsigned char b3;
} UnkStruct_0229b9bc;

extern unsigned short data_021fbe40;
extern void func_ov123_0229b65c(UnkStruct_0229b9bc *self);
extern int func_ov123_02299650(UnkStruct_0229b9bc *self, int x);
extern void func_ov123_02299630(UnkStruct_0229b9bc *self, int x);
extern void func_ov123_02299640(UnkStruct_0229b9bc *self, int x);
extern int func_ov123_022999b0(UnkStruct_0229b9bc *self, int a, int b);
extern int func_ov123_0229ac80(UnkStruct_0229b9bc *self, int a, int b, int c, int d, int e);
extern int func_ov002_02208008(UnkStruct_0229b9bc *self);
extern void func_02004644(int a, int b);
extern void func_02004658(int a);
extern void RtcSendPxiCommand(int cmd);

void func_ov123_0229b9bc(UnkStruct_0229b9bc *self)
{
    int tmp;
    int flag;

    if ((data_021fbe40 & 1) == 0) {
        func_ov123_0229b65c(self);
        if (func_ov123_02299650(self, 0x40000) != 0) {
            func_ov123_02299630(self, 0x40000);
            func_02004644(0x863, 1);
        }
        return;
    }

    tmp = func_ov002_02208008(self);
    flag = 0;

    if (func_ov123_022999b0(self, tmp, 1) != 0) {
        func_ov123_0229ac80(self, self->af, self->b0, self->a2, self->a4, 1);
        func_ov123_02299640(self, 0x40);
        RtcSendPxiCommand(0x861);

        if (self->b3 == 0) {
            flag = 1;
        } else {
            RtcSendPxiCommand(0x860);
        }
    }

    if (flag) {
        if (func_ov123_02299650(self, 0x40000) == 0) {
            func_ov123_02299640(self, 0x40000);
            func_02004658(0x863);
        }
    } else {
        if (func_ov123_02299650(self, 0x40000) != 0) {
            func_ov123_02299630(self, 0x40000);
            func_02004644(0x863, 1);
        }
    }
}
