/* func_0208d898 @ 0x0208d898, 0x68 bytes, Thumb, module main
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
    char pad_00[0x3c];
    struct InnerStruct *unk_3C;
    char pad1[0x4d - 0x40];
    unsigned char unk_4D;
    char pad2[0x4f - 0x4e];
    unsigned char unk_4F;
};

extern struct InnerStruct *func_020a9034(int a, int b, int c);
extern void func_02051694(struct InnerStruct *p);

extern unsigned char data_021c81d4[];

void func_0208d898(struct OuterStruct *arg)
{
    if (arg->unk_3C != 0) {
        return;
    }
    arg->unk_3C = func_020a9034((arg->unk_4F != 0) ? 0xf6 : 0xaa, 2, 1);
    if (arg->unk_3C != 0) {
        arg->unk_3C->unk_2C = 4;
        arg->unk_3C->unk_50 = 2;
        arg->unk_3C->unk_55 = 1;
        arg->unk_3C->unk_39 = 0;
        arg->unk_3C->unk_38 = 9;
        arg->unk_3C->unk_28 = (unsigned int) data_021c81d4;
        func_02051694(arg->unk_3C);
        arg->unk_4D = 1;
    }
}
