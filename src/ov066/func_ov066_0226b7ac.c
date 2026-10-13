/* func_ov066_0226b7ac @ 0x0226b7ac, 0x6c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_0226b7ac UnkStruct_0226b7ac;
struct UnkStruct_0226b7ac {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char pad_05[25];
    short unk_1E;
    int unk_20;
    int unk_24;
    int unk_28;
    int (*unk_2C)(int);
};
extern UnkStruct_0226b7ac *data_ov066_0226be08;

void func_ov066_0226b7ac(void)
{
    unsigned char f4 = data_ov066_0226be08->unk_04;
    int (*cb)(int) = data_ov066_0226be08->unk_2C;
    int arg = data_ov066_0226be08->unk_24;
    f4 &= ~8;
    data_ov066_0226be08->unk_04 = f4;
    data_ov066_0226be08->unk_1E = 0;
    data_ov066_0226be08->unk_20 = 0;
    data_ov066_0226be08->unk_24 = 0;
    data_ov066_0226be08->unk_28 = -1;
    data_ov066_0226be08->unk_2C = 0;
    if (cb) {
        cb(arg);
    }
}
