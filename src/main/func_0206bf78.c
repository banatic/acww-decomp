/* func_0206bf78 @ 0x0206bf78, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0206bf78 {
    char pad_00[0x2c];
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0206bf78;

extern void func_020a94a4(UnkStruct_0206bf78 *param0);
extern void func_020a9354(UnkStruct_0206bf78 *param0, int param1);

void func_0206bf78(UnkStruct_0206bf78 *param0, int param1, int param2, unsigned char param3)
{
    if (param2 > 0) {
        func_020a94a4(param0);
        func_020a9354(param0, param1);
        param0->unk_30 = 0;
        param0->unk_34 = param2;
        param0->unk_39 = param3;
        param0->unk_38 = 0;
        param0->unk_2C = 1;
    }
}
