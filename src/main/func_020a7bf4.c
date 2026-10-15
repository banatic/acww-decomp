/* func_020a7bf4 @ 0x020a7bf4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a7bf4 {
    char pad_00[4];
    int unk_04;
    char pad_08[0x1C];
    int unk_24;
    char pad_28[0x28];
    int unk_50;
} UnkStruct_020a7bf4;

typedef struct UnkStruct_020a7bf4_2 {
    char pad_00[0x18];
    unsigned char unk_18;
} UnkStruct_020a7bf4_2;

extern UnkStruct_020a7bf4 data_021f4548;
extern UnkStruct_020a7bf4_2 data_021f4588;

extern void func_020a7a64(UnkStruct_020a7bf4 *p);
extern void func_020a9354(UnkStruct_020a7bf4 *p, int a);
extern int func_020a92d8(UnkStruct_020a7bf4 *p, int a);

int func_020a7bf4(int a, int b)
{
    func_020a7a64(&data_021f4548);
    data_021f4548.unk_24 = 4;
    data_021f4548.unk_50 = b;
    func_020a9354(&data_021f4548, a);
    func_020a92d8(&data_021f4548, 0);
    if (data_021f4588.unk_18 != 0) {
        return data_021f4548.unk_04;
    }
    return 0;
}
