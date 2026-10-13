/* func_020997f8 @ 0x020997f8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020997f8 {
    unsigned char pad_00[0x243d];
    unsigned char field : 3;
};

unsigned int func_020997f8(struct UnkStruct_020997f8 *arg)
{
    return arg->field;
}
