/* func_0208daa0 @ 0x0208daa0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Result Result;
struct Result {
    char pad_00[0x28];
    void *unk_28;
    int unk_2C;
    char pad1[0x8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x16];
    int unk_50;
    char pad_54[0x1];
    unsigned char unk_55;
};

typedef struct UnkStruct_0208daa0 {
    char pad_00[0x28];
    Result *unk_28;
    char pad1[0x1c];
    unsigned char unk_48;
    char pad2[0x6];
    unsigned char unk_4F;
} UnkStruct_0208daa0;

extern void *func_020a9034(int, int, int);
extern void func_02051694(void *);

extern unsigned char data_021c82e8[];

void func_0208daa0(UnkStruct_0208daa0 *self)
{
    int value;

    if (self->unk_28 != 0) {
        return;
    }

    if (self->unk_4F != 0) {
        value = 0x94;
    } else {
        value = 0x80;
    }

    self->unk_28 = func_020a9034(value, 3, 2);
    if (self->unk_28 != 0) {
        self->unk_28->unk_2C = 4;
        self->unk_28->unk_50 = 2;
        self->unk_28->unk_55 = 1;
        self->unk_28->unk_39 = 0;
        self->unk_28->unk_38 = 0xC;
        self->unk_28->unk_28 = (void *) data_021c82e8;
        func_02051694(self->unk_28);
        self->unk_48 = 1;
    }
}
