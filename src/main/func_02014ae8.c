/* func_02014ae8 @ 0x02014ae8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020df2a0;
extern void func_02068434(int arg);

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x68];
    unsigned char unk_AC;
} UnkStruct_02014ae8;

int func_02014ae8(UnkStruct_02014ae8 *arg)
{
    if (data_020df2a0 != -1) {
        return 0;
    }
    if (arg->unk_40) {
        func_02068434(arg->unk_40);
    }
    arg->unk_AC = 3;
    return 1;
}
