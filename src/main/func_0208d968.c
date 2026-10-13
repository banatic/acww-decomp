/* func_0208d968 @ 0x0208d968, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct InnerStruct {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    char pad1[0x38 - 0x30];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x50 - 0x3a];
    unsigned int unk_50;
    char pad_54[0x55 - 0x54];
    unsigned char unk_55;
};

struct OuterStruct {
    char pad_00[0x34];
    struct InnerStruct *unk_34;
    char pad1[0x13];
    unsigned char unk_4B;
    char pad2[3];
    unsigned char unk_4F;
};

extern struct InnerStruct *func_020a9034(int a, int b, int c);
extern void func_02051694(struct InnerStruct *p);

extern unsigned char data_021c81d4[];

void func_0208d968(struct OuterStruct *arg)
{
    if (arg->unk_34 != 0) {
        return;
    }
    arg->unk_34 = func_020a9034((arg->unk_4F != 0) ? 0xd4 : 0x88, 2, 1);
    if (arg->unk_34 != 0) {
        arg->unk_34->unk_2C = 4;
        arg->unk_34->unk_50 = 2;
        arg->unk_34->unk_55 = 1;
        arg->unk_34->unk_39 = 0;
        arg->unk_34->unk_38 = 9;
        arg->unk_34->unk_28 = (unsigned int) data_021c81d4;
        func_02051694(arg->unk_34);
        arg->unk_4B = 1;
    }
}
