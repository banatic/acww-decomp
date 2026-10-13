/* func_02015d68 @ 0x02015d68, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x55];
    unsigned char unk_55;
} UnkStruct_02015d68;

extern int func_02015d78(UnkStruct_02015d68 *ptr, unsigned char val);

int func_02015d68(UnkStruct_02015d68 *ptr)
{
    return func_02015d78(ptr, ptr->unk_55);
}
