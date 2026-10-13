/* func_ov046_02261820 @ 0x02261820, 0x64 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02261820_3 {
    int unk_00;
    char pad1[0x18];
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned char unk_20;
} UnkStruct_02261820_3;

typedef struct UnkStruct_02261820 {
    char pad_00[0x28];
    int unk_28;
    UnkStruct_02261820_3 sub;
} UnkStruct_02261820;

struct Src {
    int a;
    int b;
    int c;
};

struct UnkStruct_02261820_2 {
    unsigned char unk_00;
    char pad1[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    char pad_19[3];
    unsigned short unk_1C;
    unsigned short unk_1E;
    char pad_20[4];
    unsigned short unk_24;
    unsigned short unk_26;
    char pad_28[2];
    unsigned char unk_2A;
    char pad_2B[0x31];
    int unk_5C;
    unsigned char unk_60;
    char pad_61[3];
    int unk_64;
};

extern int func_02019c20(UnkStruct_02261820 *s, int x, int v, char c, unsigned short a, unsigned short b);
extern void func_0201ad18(struct UnkStruct_02261820_2 *s, unsigned char b, int arg2, int y, struct Src *src, int arg6,
                          int arg7, unsigned char arg8);

extern int data_021fbee8;
extern unsigned int data_020c814c;

int func_ov046_02261820(unsigned char *self)
{
    func_02019c20((UnkStruct_02261820 *) (self + 0x564), 1, 0xf0, 0, *(unsigned short *) (self + 0x73c), 0);
    func_0201ad18((struct UnkStruct_02261820_2 *) (self + 0x3b0), 0, 0, 0, (struct Src *) &data_021fbee8, 4, data_020c814c, 1);
    *(unsigned char *) (self + 0x73e) = 1;
    return 1;
}
