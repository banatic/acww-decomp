/* func_02010134 @ 0x02010134, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205e1bc(void *ptr);

struct UnkStruct_02010134 {
    char pad_00[0x428];
    char unk_428[1];
    char pad_429[0x86B];
    int unk_C94;
};

void func_02010134(struct UnkStruct_02010134 *unk)
{
    if (unk->unk_C94 == 1) {
        if (func_0205e1bc(unk->unk_428)) {
            unk->unk_C94 = 2;
        }
    }
}
