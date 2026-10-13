/* func_020694dc @ 0x020694dc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void *ptr, unsigned int val);

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
} UnkStruct_020694dc;

void func_020694dc(UnkStruct_020694dc *arg)
{
    func_0206b97c(arg, arg->unk_24 + 0x14b8);
}
