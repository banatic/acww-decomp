/* func_ov121_0229b184 @ 0x0229b184, 0x90 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb2];
    unsigned char unk_B2;
    unsigned char unk_B3;
    unsigned char pad_B4[0x3a8 - 0xb4];
    int unk_3A8;
    unsigned char pad_3AC[0x528 - 0x3ac];
    int unk_528;
} UnkStruct_0229b184;

extern int func_0206f56c(void);
extern void func_ov121_0229a53c(UnkStruct_0229b184 *this);
extern int func_0208e484(int *field_3a8);
extern int func_ov121_0229ab80(UnkStruct_0229b184 *this, int b3);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_02209114(int *field_528, int b3, int r5);
extern unsigned char *func_ov002_02208098(UnkStruct_0229b184 *this, unsigned char value);

void func_ov121_0229b184(UnkStruct_0229b184 *this)
{
    if (func_0206f56c()) {
        func_ov121_0229a53c(this);
        return;
    }

    if (func_0208e484(&this->unk_3A8)) {
        int r5;

        this->unk_B2 = (unsigned char) func_ov121_0229ab80(this, this->unk_B3);
        r5 = 1;
        switch (this->unk_B2) {
            case 0:
            case 1:
            case 2:
            case 3:
                RtcSendPxiCommand(0x50);
                break;
            case 4:
            case 5:
                break;
            case 6:
                r5 = 0;
                break;
        }

        func_ov002_02209114(&this->unk_528, this->unk_B3, r5);
        func_ov002_02208098(this, 0xf);
    }
}
