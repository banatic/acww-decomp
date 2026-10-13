/* func_020a93dc @ 0x020a93dc, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a93dc;
typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_020a93dc_2;
void func_020a93dc(UnkStruct_020a93dc *a, UnkStruct_020a93dc_2 *b)
{
    a->unk_04 = a->unk_04 - b->unk_02;
}
