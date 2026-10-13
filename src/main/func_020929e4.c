/* func_020929e4 @ 0x020929e4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020929e4 {
    char pad_00[0xc];
    unsigned char *ptr;
};

extern void func_02094bc0(struct UnkStruct_020929e4 *param);

void func_020929e4(struct UnkStruct_020929e4 *param)
{
    func_02094bc0(param);
    param->ptr[0x68] = 1;
}
