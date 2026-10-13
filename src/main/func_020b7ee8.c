/* func_020b7ee8 @ 0x020b7ee8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030690(void *ptr);

typedef struct {
    unsigned char pad_00[0x14];
    unsigned int unk_14;
    unsigned char unk_18;
    unsigned char pad_19[3];
    unsigned int unk_1C;
} UnkStruct_020b7ee8;

UnkStruct_020b7ee8 *func_020b7ee8(UnkStruct_020b7ee8 *ptr)
{
    func_02030690(ptr);
    ptr->unk_14 = 0;
    ptr->unk_1C = 0;
    ptr->unk_18 = 0xff;
    return ptr;
}
