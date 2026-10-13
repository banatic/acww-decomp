/* func_0203efb0 @ 0x0203efb0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203efb0 {
    char pad_00[0xc];
    unsigned short unk_0C;
    char pad_0E[0xce];
    unsigned int unk_DC;
};

void func_0203efb0(struct UnkStruct_0203efb0 *arg0, unsigned int arg1)
{
    arg0->unk_DC = arg1 | ((unsigned int) arg0->unk_0C << 16);
}
