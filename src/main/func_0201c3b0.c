/* func_0201c3b0 @ 0x0201c3b0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201c3b0 {
    char pad_00[0x5c];
    char unk_5C;
    char pad_5D[0x8e - 0x5c - 1];
    short unk_8E;
};

extern short func_0200322c(char *ptr, int arg);
extern int func_0201c3dc(int value);

int func_0201c3b0(struct UnkStruct_0201c3b0 *param1, short *param2, int param3)
{
    *param2 = func_0200322c(&param1->unk_5C, param3);
    return func_0201c3dc((short) (*param2 - param1->unk_8E));
}
