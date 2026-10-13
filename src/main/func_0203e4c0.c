/* func_0203e4c0 @ 0x0203e4c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x15];
    unsigned char check;
} UnkStruct_0203e4c0;

extern UnkStruct_0203e4c0 *data_021c72b8;

int func_0203e4c0(unsigned char param)
{
    UnkStruct_0203e4c0 *ptr = data_021c72b8;

    if (ptr == 0) {
        return 0;
    }
    if (ptr->check == param) {
        return 1;
    }
    return 0;
}
