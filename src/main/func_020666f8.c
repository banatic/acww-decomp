/* func_020666f8 @ 0x020666f8, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020666f8 {
    unsigned char pad_00[0x1E];
    unsigned char flag;
};

void *func_020666f8(struct UnkStruct_020666f8 *arg0)
{
    if (arg0->flag == 3 || arg0->flag == 5) {
        return arg0;
    } else {
        return 0;
    }
}
