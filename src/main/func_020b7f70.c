/* func_020b7f70 @ 0x020b7f70, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
} UnkStruct_020b7f70;

extern void func_0202f27c(UnkStruct_020b7f70 *);

UnkStruct_020b7f70 *func_020b7f70(UnkStruct_020b7f70 *ptr)
{
    func_0202f27c(ptr);
    ptr->unk_14 = 0;
    ptr->unk_10 = 0;
    ptr->unk_18 = 0;
    return ptr;
}
