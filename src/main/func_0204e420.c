/* func_0204e420 @ 0x0204e420, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204e420 {
    char pad_00[0x1c];
    void *unk_1C;
};
extern int func_02030bac(void *);
int func_0204e420(struct UnkStruct_0204e420 *ptr)
{
    return func_02030bac(ptr->unk_1C);
}
