/* func_020ab91c @ 0x020ab91c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
} UnkStruct_020ab91c;

void func_020ab91c(UnkStruct_020ab91c *arg0, int arg1, int arg2)
{
    arg0->unk_A4 = arg1;
    arg0->unk_A8 = arg2;
}
