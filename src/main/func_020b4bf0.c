/* func_020b4bf0 @ 0x020b4bf0, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a92d8(void *ptr, int arg);

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[0x14];
    int unk_3C;
} UnkStruct_020b4bf0;

void func_020b4bf0(UnkStruct_020b4bf0 *ptr, int value)
{
    ptr->unk_24 = 2;
    ptr->unk_3C = value;
    func_020a92d8(ptr, 0);
    ptr->unk_24 = 0;
}
