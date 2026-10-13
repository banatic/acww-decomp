/* func_0201abe8 @ 0x0201abe8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0201abe8;

extern int func_020ea9e4(UnkStruct_0201abe8 *a, UnkStruct_0201abe8 *b);
extern int func_020e8ed8(int a, int b);

short func_0201abe8(int param1, UnkStruct_0201abe8 *param2, UnkStruct_0201abe8 *param3, int param4)
{
    int t = func_020ea9e4(param2, param3);
    return func_020e8ed8(param2->unk_04 - param3->unk_04, t) - param4;
}
