/* func_02030864 @ 0x02030864, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02030864 {
    char header[300];
    int value;
};

extern struct UnkStruct_02030864 *data_020da1a8;

int func_02030864(int value)
{
    if (data_020da1a8->value == -1) {
        data_020da1a8->value = value;
        return 1;
    }
    return 0;
}
