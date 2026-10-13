/* func_02037fd0 @ 0x02037fd0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xbc];
    int unk_BC;
    int unk_C0;
    char pad_C4[4];
    char unk_C8;
} UnkStruct_02037fd0;

void func_02037fd0(UnkStruct_02037fd0 *obj)
{
    obj->unk_BC = 7;
    obj->unk_C0 = 1;
    obj->unk_C8 = 1;
}
