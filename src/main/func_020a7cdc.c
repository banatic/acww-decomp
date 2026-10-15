/* func_020a7cdc @ 0x020a7cdc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7a64(void *p);
extern void func_020a9354(void *p, int v);
extern int func_020a92d8(void *p, int v);

typedef struct {
    char pad_00[0x24];
    int unk_24;
    char pad_28[0x10];
    int unk_38;
    char pad_3C[0x04];
    int unk_40;
    int unk_44;
} Global1;

typedef struct {
    char pad_00[0x18];
    unsigned char unk_18;
} Global2;

extern Global1 data_021f4548;
extern Global2 data_021f4588;

int func_020a7cdc(int param1, int param2, int param3)
{
    func_020a7a64(&data_021f4548);

    data_021f4548.unk_24 = 0;
    data_021f4548.unk_40 = param2;
    data_021f4548.unk_44 = param3;

    func_020a9354(&data_021f4548, param1);
    func_020a92d8(&data_021f4548, 0);

    if (data_021f4588.unk_18 != 0) {
        return data_021f4548.unk_38;
    } else {
        return 0;
    }
}
