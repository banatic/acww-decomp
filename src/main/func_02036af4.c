/* func_02036af4 @ 0x02036af4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02036af4 {
    unsigned char pad_00[0xa];
    unsigned short unk_0A;
};
extern void func_02035638(unsigned short value);
void func_02036af4(struct UnkStruct_02036af4 *ptr)
{
    if (ptr->unk_0A != 0xffff) {
        func_02035638(ptr->unk_0A);
        ptr->unk_0A = 0xffff;
    }
}
