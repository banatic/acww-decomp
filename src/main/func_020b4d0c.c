/* func_020b4d0c @ 0x020b4d0c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7c98(int, int);

struct UnkStruct_020b4d0c {
    char pad_00[0x24];
    int unk_24;
};

struct UnkStruct_020b4d0c_2 {
    int arr[15];
};

extern struct UnkStruct_020b4d0c_2 data_020e5294;

int func_020b4d0c(struct UnkStruct_020b4d0c *param)
{
    struct UnkStruct_020b4d0c_2 local;
    int i;
    int result = 1;
    int value;

    local = data_020e5294;
    value = func_020a7c98(param->unk_24 + 0xafc, 0);
    for (i = 0; i < 15; i++) {
        if (local.arr[i] == value) {
            result = 0;
            break;
        }
    }
    return result;
}
