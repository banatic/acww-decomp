/* func_020a7c98 @ 0x020a7c98, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7a64(void *p);
extern int func_020a9354(void *p, int a);
extern int func_020a92d8(void *p, int a);

struct UnkStruct_020a7c98 {
    char pad_00[0x18];
    unsigned char unk_18;
    char pad_19[0x24 - 0x19];
    int unk_24;
    char pad_28[0x3c - 0x28];
    int unk_3C;
    char pad_40[0x48 - 0x40];
    int unk_48;
};

struct SomeOtherStruct {
    char pad_00[0x18];
    unsigned char unk_18;
};

extern struct UnkStruct_020a7c98 data_021f4548;
extern struct SomeOtherStruct data_021f4588;

int func_020a7c98(int a, int b)
{
    func_020a7a64(&data_021f4548);
    data_021f4548.unk_24 = 1;
    data_021f4548.unk_48 = b;
    func_020a9354(&data_021f4548, a);
    func_020a92d8(&data_021f4548, 0);
    if (data_021f4588.unk_18) {
        return data_021f4548.unk_3C;
    }
    return 0;
}
