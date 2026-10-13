/* func_02036b50 @ 0x02036b50, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020356c4(int, int, int, int);

struct UnkStruct_02036b50 {
    unsigned char pad_00[14];
    unsigned short unk_0E;
};

void func_02036b50(struct UnkStruct_02036b50 *arg0, int arg1)
{
    func_020356c4(0x22, arg1, 0x7f, 0);
    arg0->unk_0E = arg1;
}
