/* func_020b8038 @ 0x020b8038, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202ff00(void *ptr);

struct UnkStruct_020b8038 {
    unsigned int unk_00;
    unsigned char pad_04[0x34];
    unsigned int unk_38;
    unsigned int unk_3C;
    unsigned char unk_40;
};

extern unsigned char data_020e5810[];

void *func_020b8038(struct UnkStruct_020b8038 *ptr)
{
    func_0202ff00(ptr);
    ptr->unk_00 = (unsigned int) data_020e5810;
    ptr->unk_3C = 0;
    ptr->unk_38 = 0;
    ptr->unk_40 = 0xFF;
    return ptr;
}
