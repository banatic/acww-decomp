/* func_ov004_0220c054 @ 0x0220c054, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0220c054 {
    int unk_00;
    void *unk_04;
};

struct UnkStruct_0220c054_2 {
    char pad_00[0x12c];
    struct UnkStruct_0220c054 *unk_12C;
};

extern void func_ov004_0220c144(struct UnkStruct_0220c054_2 *obj, int arg);

void func_ov004_0220c054(struct UnkStruct_0220c054_2 *obj)
{
    if (obj->unk_12C != 0) {
        if (obj->unk_12C->unk_04 != 0) {
            func_ov004_0220c144(obj, 2);
        }
    }
}
