/* func_020794a8 @ 0x020794a8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020794a8 {
    unsigned char pad_00[0x1a];
    unsigned short unk_1A;
};

void func_020794a8(struct UnkStruct_020794a8 *obj, int add)
{
    int sum = obj->unk_1A + add;
    if (sum >= 0xFFFF) {
        obj->unk_1A = 0xFFFF;
    } else {
        obj->unk_1A = sum;
    }
}
