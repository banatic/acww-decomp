/* func_02036470 @ 0x02036470, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020c9f1c[];

struct UnkStruct_02036470 {
    char pad_00[0x20];
    unsigned int unk_20;
};

void func_02036470(struct UnkStruct_02036470 *obj, int index)
{
    obj->unk_20 = data_020c9f1c[index];
}
