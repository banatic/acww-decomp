/* func_020a7c38 @ 0x020a7c38, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x24];
    int unk_4C;
} UnkStruct_020a7c38;

typedef struct {
    unsigned char pad_00[0x18];
    unsigned char unk_18;
} UnkStruct_020a7c38_2;

extern UnkStruct_020a7c38 data_021f4548;
extern UnkStruct_020a7c38_2 data_021f4588;

extern void func_020a7a64(UnkStruct_020a7c38 *ptr);
extern void func_020a9354(UnkStruct_020a7c38 *ptr, int arg);
extern void func_020a92d8(UnkStruct_020a7c38 *ptr, int arg);

int func_020a7c38(int param)
{
    func_020a7a64(&data_021f4548);
    data_021f4548.unk_24 = 3;
    func_020a9354(&data_021f4548, param);
    func_020a92d8(&data_021f4548, 0);
    if (data_021f4588.unk_18) {
        return data_021f4548.unk_4C;
    } else {
        return 0;
    }
}
