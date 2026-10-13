/* func_0200f5e4 @ 0x0200f5e4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200f5e4 {
    char pad_00[0x60];
    int unk_60;
    char pad_64[0x800 - 0x64];
    int unk_800;
} UnkStruct_0200f5e4;

typedef struct UnkStruct_0200f5e4_2 {
    char pad_00[4];
    int unk_04;
} UnkStruct_0200f5e4_2;

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0200f290(UnkStruct_0200f5e4 *, int);
extern int func_0200e9a8(UnkStruct_0200f5e4 *, unsigned char *, UnkStruct_0200f5e4_2 *, char *, int);
extern int func_020b65c4(void);

int func_0200f5e4(UnkStruct_0200f5e4 *param1, UnkStruct_0200f5e4_2 *param2, int param3)
{
    unsigned char local;

    if (func_02073908(data_020ccf94, param1->unk_800)) {
        return 0;
    }
    if (func_0200f290(param1, 0x10)) {
        return 0;
    }
    param2->unk_04 = param1->unk_60;
    if (func_0200e9a8(param1, &local, param2, (char *) param2 + 8, param3) == 0) {
        return 0;
    }
    if (local == func_020b65c4()) {
        return 1;
    } else {
        return 0;
    }
}
