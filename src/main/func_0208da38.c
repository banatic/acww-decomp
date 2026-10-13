/* func_0208da38 @ 0x0208da38, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c82e8;
typedef struct UnkStruct_0208da38 UnkStruct_0208da38;
typedef struct UnkStruct_0208da38_2 UnkStruct_0208da38_2;

struct UnkStruct_0208da38 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    char pad_30[8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[22];
    int unk_50;
    char pad_54[1];
    unsigned char unk_55;
};

struct UnkStruct_0208da38_2 {
    char pad_00[0x2c];
    UnkStruct_0208da38 *unk_2C;
    char pad_30[25];
    unsigned char unk_49;
    char pad2[5];
    unsigned char unk_4F;
};

extern UnkStruct_0208da38 *func_020a9034(int, int, int);
extern void func_02051694(UnkStruct_0208da38 *);

void func_0208da38(UnkStruct_0208da38_2 *this)
{
    if (this->unk_2C) {
        return;
    }
    this->unk_2C = func_020a9034((this->unk_4F != 0) ? 0x97 : 0x83, 3, 2);
    if (this->unk_2C == 0) {
        return;
    }
    this->unk_2C->unk_2C = 4;
    this->unk_2C->unk_50 = 2;
    this->unk_2C->unk_55 = 1;
    this->unk_2C->unk_39 = 0;
    this->unk_2C->unk_38 = 0xc;
    this->unk_2C->unk_28 = (int) &data_021c82e8;
    func_02051694(this->unk_2C);
    this->unk_49 = 1;
}
